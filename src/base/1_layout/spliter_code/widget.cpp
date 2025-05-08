#include "widget.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QTextBrowser>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    this->setWindowTitle("Qt分裂器布局");

    // 整体使用水平分裂器
    QHBoxLayout* pHLay = new QHBoxLayout(this);

    // 整体的水平分裂器
    QSplitter* pHSplitter  = new QSplitter(Qt::Horizontal, this);
    QWidget*   pLeftWidget = new QWidget(this);
    pLeftWidget->setStyleSheet("background-color:rgb(54,54,54)");
    pLeftWidget->setMinimumWidth(200);

    // 分裂器添加widget
    pHSplitter->addWidget(pLeftWidget);

    // 右侧的竖直分裂器
    // 注意参数pHSplitter，表示父指针
    QSplitter* pVSplitter = new QSplitter(Qt::Vertical, pHSplitter);
    pVSplitter->setOpaqueResize(false);

    QWidget* pRightTopWidget = new QWidget(this);
    pRightTopWidget->setStyleSheet("background-color:rgb(154, 154, 154)");

    QTextBrowser* pRightBottom = new QTextBrowser(this);

    pVSplitter->addWidget(pRightTopWidget);
    pVSplitter->addWidget(pRightBottom);

    pHSplitter->addWidget(pVSplitter);

    // 布局添加分裂器
    pHLay->addWidget(pHSplitter);

    // 设置整体布局
    setLayout(pHLay);
}

Widget::~Widget() {}
