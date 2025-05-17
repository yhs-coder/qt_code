#include "widget.h"

#include <QMouseEvent>

Widget::Widget(QWidget *parent) : QWidget(parent) { this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint); }

Widget::~Widget() {}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mouse_pos  = event->globalPos();
    window_pos = this->pos();
    diff_pos   = mouse_pos - window_pos;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->globalPos();
    this->move(pos - diff_pos);
}
