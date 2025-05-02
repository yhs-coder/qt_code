#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// 点击按钮，设置文本和图标
void Widget::on_btnStart_clicked()
{
    // 获取按钮文本内容
    QString text = ui->btnStart->text();
    if (text == "启动") {
        // 设置文本为 '停止'
        ui->btnStart->setText("停止");
        // 设置字体
        ui->btnStart->setFont(QFont("黑体", 16));
        // 设置图标和图标大小
        ui->btnStart->setIcon(QIcon(":/icon/stop.ico"));
        ui->btnStart->setIconSize(QSize(48, 48));
    } else {
        ui->btnStart->setText("启动");
        ui->btnStart->setFont(QFont("宋体", 14));
        ui->btnStart->setIcon(QIcon(":/icon/start.ico"));
        ui->btnStart->setIconSize(QSize(32, 32));
    }
}

// 使能禁能按钮
void Widget::on_btnConnect_clicked()
{
    QString text = ui->btnConnect->text();
    if (text == "连接") {
        ui->btnConnect->setText("取消连接");
        ui->btnSend->setEnabled(true);
    }else {
        ui->btnConnect->setText("连接");
        ui->btnSend->setEnabled(false);
    }
}

// 在按钮按下至抬起时，才发射clicked信号
void Widget::on_btnSignal_clicked()
{
    qDebug() << "clicked...";
}

// 按钮按下时，发射pressed信号
void Widget::on_btnSignal_pressed()
{
    qDebug() << "pressed...";
}


// 按钮抬起时，发射released信号
void Widget::on_btnSignal_released()
{
     qDebug() << "released...";
}

