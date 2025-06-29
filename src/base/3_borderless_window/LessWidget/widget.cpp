#include "widget.h"

#include <QMouseEvent>

Widget::Widget(QWidget *parent) : QWidget(parent) { this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint); }

Widget::~Widget() {}

void Widget::mousePressEvent(QMouseEvent *event)
{
    // 鼠标位置相对于桌面原点的绝对位置
    mouse_pos = event->globalPos();
    // 程序窗口左上角位置相对于桌面原点的绝对位置
    window_pos = this->pos();
    // 鼠标与窗口位置的相对路径
    diff_pos = mouse_pos - window_pos;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    // 获取鼠标移动后的位置
    QPoint pos = event->globalPos();
    // 鼠标新位置减去与窗口的相对路径
    this->move(pos - diff_pos);
}
