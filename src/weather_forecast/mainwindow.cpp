#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);  // 设置窗口无边框
    this->setFixedSize(width(), height());         // 设置固定窗口大小
}

MainWindow::~MainWindow() { delete ui; }
