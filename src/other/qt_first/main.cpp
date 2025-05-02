#include "mainwindow.h"
#include <QApplication>

//Qt程序入口
int main(int argc, char *argv[])
{
    // 应用程序对象，在Qt程序中有且仅有一个
    QApplication a(argc, argv);

    // 自定义窗口对象
    MainWindow w;
    // 窗口对象默认不会显示，调用show进行显示
    w.show();

    // 进行消息循环，起阻塞作用
    return a.exec();
}
