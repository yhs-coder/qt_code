#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);  // 设置窗口无边框
    this->setFixedSize(width(), height());         // 设置固定窗口大小

    // 构建右键菜单
    mExitMenu = new QMenu(this);
    mExitAct  = new QAction(this);

    mExitAct->setText("退出");
    mExitAct->setIcon(QIcon(":/res/close.png"));

    mExitMenu->addAction(mExitAct);

    connect(mExitAct, QAction::triggered, this, [=] { qApp->exit(0); });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    // 弹出右键菜单
    mExitMenu->exec(QCursor::pos());
}
