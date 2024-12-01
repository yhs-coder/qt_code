#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 1.下载
    ui->pbDownload->setMinimum(0);
    ui->pbDownload->setMaximum(100);
    // ui->pbDownload->setRange(0, 100);

    // 设置文本的显示位置
    ui->pbDownload->setAlignment(Qt::AlignRight);
    // 设置是否显示文本
    // ui->pbDownload->setTextVisible(false);

    mTimerDownload = new QTimer();
    mTimerDownload->setInterval(100);

    connect(ui->btnDownload, &QPushButton::clicked, this, &Widget::onBtnDownloadClicked);
    connect(mTimerDownload, &QTimer::timeout, this, &Widget::onDownloadTimeout);

    // 2.拷贝
    ui->pbCopy->setMinimum(0);
    ui->pbCopy->setMaximum(1000);
    // ui->pbCopy->setRange(0, 1000);

    mTimerCopy = new QTimer();
    mTimerCopy->setInterval(12);

    connect(ui->btnCopy, &QPushButton::clicked, this, &Widget::onBtnCopyClicked);
    connect(mTimerCopy, &QTimer::timeout, this, &Widget::onCopyTimeout);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnDownloadClicked()
{
    ui->pbDownload->reset();
    mTimerDownload->start();
}

void Widget::onDownloadTimeout()
{
    int currentValue = ui->pbDownload->value();

    if(currentValue >= ui->pbDownload->maximum()) {
        mTimerDownload->stop();
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

    if(currentValue >= ui->pbCopy->maximum()) {
        mTimerCopy->stop();
        QMessageBox::information(this, "提示", "文件拷贝完成！");
    } else {
        ui->pbCopy->setValue(ui->pbCopy->value() + 1);
        qDebug() << ui->pbCopy->value();
    }
}

