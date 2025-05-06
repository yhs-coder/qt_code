#include "widget.h"

#include <QDebug>

#include "./ui_widget.h"
#include "setdialog.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "ui thread id = " << QThread::currentThreadId();

    ui->comboBox->addItem("1");
    ui->comboBox->addItem("2");
    ui->comboBox->addItem("3");
    ui->comboBox->addItem("4");

    // 使用泛型解决信号重载问题 （也可以使用Qt4的写法，指定参数类型）
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget::onIndex);
    connect(ui->comboBox, QOverload<const QString&>::of(&QComboBox::currentIndexChanged), this, &Widget::onIndexStr);
}

Widget::~Widget() { delete ui; }

void Widget::on_btnSet_clicked()
{
    SetDialog dlg;

    connect(&dlg, &SetDialog::sig_addOne, this, [&](int num) { ui->lineEdit->setText(QString::number(num)); });

    // 打开对话框，并且事件循环，UI阻塞
    // 需要再执行exec之前，绑定信号槽
    dlg.exec();
}

void Widget::on_btnUpdate_clicked()
{
    std::unique_ptr<ChildThread> thread(new ChildThread());
    // connect(thread.get(), &ChildThread::sig_sendToUI, [&](Score s) {
    //     string info = s.name + "id = " + to_string(s.id) + " age = " + to_string(s.age);
    //     ui->lineInfo->setText(QString::fromStdString(info));
    //     // lambda表达式中的线程是ChildThread，并给ui主线程
    //     qDebug() << "slot thread id = " << QThread::currentThreadId();
    // });

    connect(thread.get(), &ChildThread::sig_sendToUI, this, &Widget::showInfo);
    connect(thread.get(), &ChildThread::sig2, this, &Widget::showInfo2);

    thread->start();
    qDebug() << "ui thread id2 = " << QThread::currentThreadId();

    thread->wait();  // 阻塞直到线程结束
    // thread 析构时已安全退出
}

void Widget::showInfo(Score s)
{
    qDebug() << "ui thread id3 = " << QThread::currentThreadId();
    string info = s.name + " id = " + to_string(s.id) + " age = " + to_string(s.age);
    ui->lineInfo->setText(QString::fromStdString(info));
}

void Widget::showInfo2(string name, int id)
{
    qDebug() << "name = " << QString::fromStdString(name);
    qDebug() << "id = " << id;
}

void Widget::onIndex(int index) {}
void Widget::onIndexStr(const QString& index) {}
