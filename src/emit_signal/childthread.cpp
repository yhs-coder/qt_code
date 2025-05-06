#include "childthread.h"

#include <QDebug>

ChildThread::ChildThread(QObject *parent) : QThread{parent}
{
    // 当信号发送的参数不是内置类型时，需要主动注册参数类型
    qRegisterMetaType<Score>("Score");
    qRegisterMetaType<string>("string");
}

void ChildThread::run()
{
    qDebug() << "run thread id = " << QThread::currentThreadId();
    //    while(1)
    //    {
    Score s;
    s.name = "jack";
    s.id   = 1001;
    s.age  = 100;

    // 在线程中发射信号，由主线程(ui)去接收处理
    emit sig_sendToUI(s);
    emit sig2("tom", 10, 20);
    //}
}
