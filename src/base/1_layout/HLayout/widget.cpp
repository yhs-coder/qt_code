#include "widget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    // 重置窗口大小
    this->resize(400, 80);

    QLabel* pPath = new QLabel(this);
    pPath->setObjectName("pPath");
    pPath->setText("路径");

    QLineEdit* pEdit = new QLineEdit(this);
    pEdit->setObjectName("pEdit");
    pEdit->setMinimumWidth(50);

    QPushButton* pBtn = new QPushButton(this);
    pBtn->setObjectName("pBtn");
    pBtn->setText("选择");

    // 创建水平布局
    QHBoxLayout* pHLay = new QHBoxLayout(this);

    // 相邻控件之间默认的间隙为 7
    qDebug() << pHLay->spacing();
    // 设置相邻控件之间默认的间隙
    // (30);
    // 在水平布局左侧添加一个水平的伸缩空间（相当于加了个可拉伸的弹簧）
    pHLay->addStretch();
    // 在水平布局中添加控件
    pHLay->addWidget(pPath);

    // 在pPath和pBtn之间间隔100px
    // pHLay->addSpacing(100);

    pHLay->addWidget(pEdit);
    pHLay->addWidget(pBtn);

    // 在水平布局右侧添加一个水平的伸缩空间
    pHLay->addStretch();

    // setMargin：左上右下的间隙都设置为100
    // pHLay->setMargin(100);

    // setContentsMargins: 分别设置左上右下的间隙
    pHLay->setContentsMargins(0, 50, 10, 50);
}

Widget::~Widget() {}
