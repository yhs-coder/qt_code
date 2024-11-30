#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始化红色滑动条
    ui->hsRed->setMinimum(0);
    ui->hsRed->setMaximum(255);
    // ui->hsRed->setRange(0,255);

    // 设置步长，singleStep指的是按键盘的左右箭头（<-/->）时变化的步长
    ui->hsRed->setSingleStep(1);

    // singleStep, 指的是鼠标点击滑块两侧时变化的步长
    ui->hsRed->setPageStep(10);

    // 方向上设置为水平滑动条
    ui->hsRed->setOrientation(Qt::Horizontal);

    // 初始化绿色滑动条
    ui->hsGreen->setMinimum(0);
    ui->hsGreen->setMaximum(255);
    ui->hsGreen->setSingleStep(5);
    ui->hsGreen->setPageStep(20);
    ui->hsGreen->setOrientation(Qt::Horizontal);

    // 初始化蓝色滑动条
    ui->hsBlue->setMinimum(0);
    ui->hsBlue->setMaximum(255);
    ui->hsBlue->setSingleStep(10);
    ui->hsBlue->setPageStep(50);
    ui->hsBlue->setOrientation(Qt::Horizontal);

}

Widget::~Widget()
{
    delete ui;
}

QString Widget::getRGBValue()
{
    QString red = QString::number(ui->hsRed->value());
    QString green = QString::number(ui->hsGreen->value());
    QString blue = QString::number(ui->hsBlue->value());

    // 设置样式
    QString style = "background-color: rgb(" + red + "," + green + "," + blue + ");";
    return style;
}

void Widget::setBackgroupColor()
{
    // 获取红绿蓝rgb的颜色值
    QString rgbValue = getRGBValue();
    qDebug() << rgbValue;
    // 更新背景颜色
    ui->lineEdit->setStyleSheet(rgbValue);
}


// 滑动条值发生变化时,设置文本框的值
void Widget::on_hsRed_valueChanged(int value)
{
    ui->leRed->setText(QString::number(value));
    // 获取颜色值，更新文本编辑框背景颜色
    setBackgroupColor();
}


void Widget::on_hsGreen_valueChanged(int value)
{
    ui->leGreen->setText(QString::number(value));
    setBackgroupColor();
}


void Widget::on_hsBlue_valueChanged(int value)
{
    ui->leBlue->setText(QString::number(value));
    setBackgroupColor();
}

