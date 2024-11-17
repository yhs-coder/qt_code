#include "widget.h"
#include "ui_widget.h"
#include <QTime>
#include <QPixmap>
#include <QMessageBox>

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

void Widget::on_btnGetText_clicked()
{
    QMessageBox::information(this, "标签演示", ui->lbTime->text());
}


void Widget::on_btnSetText_clicked()
{
    // 设置文本为当前时间
    ui->lbTime->setText(QTime::currentTime().toString());
}


void Widget::on_btnSetText_6_clicked()
{
    // 设置左对齐并且垂直对齐
    ui->lbAlign->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}


void Widget::on_btnGetText_6_clicked()
{
    ui->lbAlign->setAlignment(Qt::AlignCenter);
}


void Widget::on_btnGetText_7_clicked()
{
    // 设置右对齐并且垂直对齐
    ui->lbAlign->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
}


void Widget::on_pushButton_clicked()
{
    ui->lbWrap->setWordWrap(false);
}


void Widget::on_btnEbanleWrap_clicked()
{
    ui->lbWrap->setWordWrap(true);
}


void Widget::on_btnChangeImages_clicked()
{
    QPixmap px;
    if (index == 0) {
        px.load(QString(":/icon/lemon.ico"));
        index++;
    } else {
        px.load(QString(":/icon/mango.ico"));
        index = 0;
    }
    // 将图片设置到标签上
    ui->lbImage->setPixmap(px);

    // 保持图片的宽高比，禁止缩放，否则会拉伸失真
    ui->lbImage->setScaledContents(false);
}

