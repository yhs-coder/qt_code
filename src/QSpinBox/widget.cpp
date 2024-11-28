#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 1. 设置单价

    // 设置前缀
    ui->dsbPrice->setPrefix("￥");
    // 设置范围
    // ui->dsbPrice->setRange(1.00, 99.99);

    // 设置最大值和最小值
    ui->dsbPrice->setMaximum(99.99);
    ui->dsbPrice->setMinimum(1.00);

    // 设置步长
    ui->dsbPrice->setSingleStep(0.5);

    // 设置加速
    ui->dsbPrice->setAccelerated(true);

    // 设置循环
    ui->dsbPrice->setWrapping(true);

    // 2. 设置数量

    // 设置后缀
    ui->sbWeight->setSuffix(" KG");
    // 设置范围
    ui->dsbPrice->setRange(1, 100);

    // 设置最大值和最小值
    // ui->sbWeight->setMaximum(100);
    // ui->sbWeight->setMinimum(1);

    // 设置步长
    ui->sbWeight->setSingleStep(2);

    // 设置加速
    ui->sbWeight->setAccelerated(true);

    // 设置循环
    ui->sbWeight->setWrapping(true);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_dsbPrice_valueChanged(double arg1)
{
    double price = arg1;
    int weight = ui->sbWeight->value();
    ui->leTotal->setText(QString::number(price * weight));
}


void Widget::on_sbWeight_valueChanged(int arg1)
{
    int weight = arg1;
    double price = ui->dsbPrice->value();
    ui->leTotal->setText(QString::number(price * weight));
}

