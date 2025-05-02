#include "mainwindow.h"
#include <QPushButton>

/*
命名规范：
    类名遵守大驼峰命名法，类名首字母大写，单词和单词之间首字母大写
    函数名、变量名遵守小驼峰命名法，首字母小写，单词和单词之间首字母大写

快捷键：
    运行  ctrl + r
    编译  ctrl + b
    注释  ctrl + /
    字体缩放    ctrl + 鼠标滚轮
    整行移动    ctrl + shift + ↑或↓
    自动对齐    ctrl + i
    同名的.h和.cpp文件间快速切换  F4
    查找关键字  ctrl + f
    帮助文档    F1

*/



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口尺寸
    this->resize(500,500);
    // 可设置谷固定窗口尺寸
    // this->setFixedSize(600,600);

    //设置窗口标题
    this->setWindowTitle("第一个窗口");

    // 按钮控件
    QPushButton * btn = new QPushButton;
    // btn->show(); // 以顶层的方式显示，不依赖当前窗口

    // 如果按钮想显示并依赖在当前的窗口中，需要设置父窗口
    btn->setParent(this);

    // 设置按钮文本
    btn->setText("点击");

    // 设置按钮尺寸
    btn->resize(100,30);

    // 创建第二个按钮
    QPushButton * btn2 = new QPushButton("hello", this);
    // 移动按钮位置
    btn2->move(100,0);
}

MainWindow::~MainWindow()
{
}

