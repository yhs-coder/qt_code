#include "widget.h"

#include <QMessageBox>
#include <QVBoxLayout>
// #include "./ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent)
// , ui(new Ui::Widget)
{
    // ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    initUI();

    // 处理标题栏发出的信号
    connect(m_pTitleBar, &CTitleBar::sig_close, this, &Widget::on_closeSlot);
}

Widget::~Widget()
{
    // delete ui;
}

void Widget::initUI()
{
    QWidget* widget = new QWidget(this);
    m_pTitleBar     = new CTitleBar(this);

    widget->setMinimumSize(800, 700);

    QVBoxLayout* pVlay = new QVBoxLayout(this);

    pVlay->addWidget(m_pTitleBar);
    pVlay->addWidget(widget);

    pVlay->setContentsMargins(0, 0, 0, 0);
    this->setLayout(pVlay);
}

bool Widget::nativeEvent(const QByteArray& eventType, void* message, long* result) { return false; }

void Widget::on_closeSlot()
{
    this->close();
    // QMessageBox::StandardButton _exit = QMessageBox::warning(this, "提示", "确定要退出吗", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    // if (_exit == QMessageBox::Yes) {
    //     this->close();
    // }
}
