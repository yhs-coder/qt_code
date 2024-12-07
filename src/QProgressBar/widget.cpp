#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始化下载和拷贝的定时器
    mTimerDownload = new QTimer(this);
    mTimerCopy = new QTimer(this);
    // 设置定时器时间间隔】
    mTimerDownload->setInterval(100);
    mTimerCopy->setInterval(10);

    // 绑定信号槽
    connect(ui->btnDownload, &QPushButton::clicked, this, &Widget::onBtnDownloadClicked);
    connect(mTimerDownload, &QTimer::timeout, this, &Widget::onDownloadTimeout);
    connect(ui->btnCopy, &QPushButton::clicked, this, &Widget::onBtnCopyClicked);
    connect(mTimerCopy, &QTimer::timeout, this, &Widget::onCopyTimeout);


    // 1. 设置下载进度条
    ui->pbDownload->setMinimum(0);
    ui->pbDownload->setMaximum(100);
    ui->pbDownload->setRange(0, 100);

    // 设置文本的显示位置
    // ui->pbDownload->setAlignment(Qt::AlignRight); //右对齐
    ui->pbDownload->setAlignment(Qt::AlignCenter);  // 中间对齐
    // 设置不显示文本
    // ui->pbDownload->setTextVisible(false);

    // 2. 设置拷贝进度条
    ui->pbCopy->setRange(0, 1024);
    // 设置进度条增长方向反转（从右到左）
    ui->pbCopy->setInvertedAppearance(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnDownloadClicked()
{
    // 复位当前值，即重置为0
    ui->pbDownload->reset();
    // 启动定时器
    mTimerDownload->start();
}

void Widget::onDownloadTimeout()
{
    // 获取当前值
    int currentValue = ui->pbDownload->value();
    // 检测是否达到最大值
    if (currentValue >= ui->pbDownload->maximum()) {
        // 终止定时器
        mTimerDownload->stop();
        // 弹出提示框
        QMessageBox::information(this, "提示", "文件下载完成！");
    } else {
        ui->pbDownload->setValue(ui->pbDownload->value() + 1);
        qDebug() << ui->pbDownload->value();
    }
}

void Widget::onBtnCopyClicked()
{
    ui->pbCopy->reset();
    mTimerCopy->start();
}

void Widget::onCopyTimeout()
{
    int currentValue = ui->pbCopy->value();
    // 检测是否达到最大值
    if (currentValue >= ui->pbCopy->maximum()) {
        // 终止定时器
        mTimerCopy->stop();
        // 弹出提示框
        QMessageBox::information(this, "提示", "文件拷贝完成！");
    } else {
        ui->pbCopy->setValue(ui->pbCopy->value() + 1);
        qDebug() << ui->pbCopy->value();
    }
}
