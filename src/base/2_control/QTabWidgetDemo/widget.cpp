#include "widget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTabWidget>

#include "./ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    QHBoxLayout* lay = new QHBoxLayout(this);

    // 选项卡窗口控件
    QTabWidget* pTabWidget = new QTabWidget(this);

    // 是否显示关闭按钮
    pTabWidget->setTabsClosable(true);
    // 设置选项卡窗口是否可以移动
    pTabWidget->setMovable(true);
    // 设置tab的位置
    // 不设置默认为北
    pTabWidget->setTabPosition(QTabWidget::North);

    // 设置选项卡窗口形状
    // Triangular为梯形
    // Rounded为圆形
    pTabWidget->setTabShape(QTabWidget::Rounded);

    QWidget* w1 = new QWidget;
    w1->setStyleSheet("background-color:rgb(154,54,54)");

    QWidget* w2 = new QWidget;
    w2->setStyleSheet("background-color:rgb(54,254,54)");

    QWidget* w3 = new QWidget;
    w3->setStyleSheet("background-color:rgb(0,54,154)");

    // 插入选项卡
    pTabWidget->insertTab(0, w1, "tab1");
    pTabWidget->insertTab(1, w2, "tab2");
    pTabWidget->insertTab(2, w3, "tab3");

    // 设置tab不可见
    // pTabWidget->setTabVisible(1, false);
    // 设置tab提示
    pTabWidget->setTabToolTip(2, "this is tab3");
    lay->addWidget(pTabWidget);

    // 相关的信号
    /*
    Q_SIGNALS:
        void currentChanged(int index);     // 当前选项卡发生改变
        void tabCloseRequested(int index);  // 关闭选项卡
        void tabBarClicked(int index);      // 单击
        void tabBarDoubleClicked(int index);// 双击
    */

    connect(pTabWidget, &QTabWidget::currentChanged, this, [this](int index) { qDebug() << "index = " << index; });
    connect(pTabWidget, &QTabWidget::tabCloseRequested, this, [=](int index) {
        qDebug() << "tabCloseRequested index = " << index;  // 移除tab
        pTabWidget->removeTab(index);
    });
    connect(pTabWidget, &QTabWidget::tabBarClicked, this, [=](int index) { qDebug() << "vtabBarClicked index = " << index; });
    connect(pTabWidget, &QTabWidget::tabBarDoubleClicked, this, [this](int index) { qDebug() << "tabBarDoubleClicked index = " << index; });
}

Widget::~Widget() { delete ui; }
