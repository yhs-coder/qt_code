#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ip->setText("192.168.19.222");
    setWindowTitle("流量显示器");
    // 设置按钮对应的点击事件
    connect(ui->win1, &QPushButton::clicked, this,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->win2, &QPushButton::clicked, this,[=](){
        ui->stackedWidget->setCurrentIndex(1);
        //ui->stackedWidget->setCurrentIndex(ui->page_2);
    });

    connect(ui->ipBtn, &QPushButton::clicked, ui->ip, [=](){
        ui->test->append("数据显示： ");
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

