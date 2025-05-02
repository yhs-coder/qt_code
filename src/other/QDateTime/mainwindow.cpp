#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QTime>
#include <QElapsedTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取当前的日期
    QDate d = QDate::currentDate();

    // 输出日期
    // 方式一：
    qDebug() << "year: "<< d.year() << ", month: " << d.month() << " , day: " << d.day();

    // 方式二： 格式化输出 例如 2023-11-04
    QString str = d.toString("yyyy-MM-dd");
    qDebug() << "date: " << str;

    //获取当前时间
    // 方式一
    QTime curtime = QTime::currentTime();
    qDebug() << "hour: " << curtime.hour() << ", minute: " << curtime.minute() << ", second: " << curtime.second()
             << " , millsecond: " << curtime.msec();
    // 方式二
//    QString strtime = curtime.toString("hh:mm:ss.zzz");
    QString strtime = curtime.toString("HH:mm:ss.zzz");
    qDebug() << "格式化时间： " << strtime;

    // 统计函数运行的时间
#if 0
    // 以下方式已被弃用：
    QTime tt;
    tt.start();
    randNumbers(100);
    int ms = tt.elapsed();
#else
    QElapsedTimer tt;
    tt.start();
    randNumbers(100);
    int ms = tt.elapsed();
    qDebug() << "函数执行所用的时间为： " <<ms << "毫秒";
#endif

    // 保存当前日期使时间
    QDateTime dt = QDateTime::currentDateTime();
    // 格式化输出
//    QString strdt = dt.toString("yyyy/MM/dd hh:mm:ss ap");
    QString strdt = dt.toString("yyyy/MM/dd HH:mm:ss ap");
    qDebug() << "当前的日期和时间：" << strdt;

    // 先取出日期
    d = dt.date();
    qDebug() << "year: "<< d.year() << ", month: " << d.month() << " , day: " << d.day();

    // 再取出时间
    QTime t = dt.time();
    qDebug() << "hour: " << t.hour() << ", minute: " << t.minute() << ", second: " << t.second()
             << " , millsecond: " << t.msec();

}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::randNumbers(int count)
{
    srand(time(NULL));
    for (int i = 0; i < count; i++)
    {
        int num = rand() % 10000;
        qDebug() << num;
    }
}

