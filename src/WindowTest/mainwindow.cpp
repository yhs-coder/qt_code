#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置窗口的最大尺寸
    setMaximumSize(600,600);
    // 设置窗口的最大尺寸
    setMinimumSize(400,400);
    // 设置窗口的固定尺寸
//    setFixedSize(500,500);
    // 设置窗口标题
    setWindowTitle("hello Qt!");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_moveBtn_clicked()
{
    // 获取窗口的位置信息，得到左上角的点坐标
    QRect rect = frameGeometry();
    move(rect.topLeft() + QPoint(100,200));
}


void MainWindow::on_posBtn_clicked()
{
    // 获取窗口的位置信息，得到左上角的点坐标
    QRect rect = frameGeometry();
    qDebug() << "左上角： " << rect.topLeft()
             << "右上角： " << rect.topRight()
             << "左下角： " << rect.bottomLeft()
             << "右上角： " << rect.bottomRight()
             << "宽度: " << rect.width()
             << "高度: " << rect.height();
}


void MainWindow::on_gemotryBtn_clicked()
{
    int x = 100 + rand() % 500;
    int y = 100 + rand() % 500;
    int w = width() + 10;
    int h = height() + 10;
    setGeometry(x, y, w, h);
}

