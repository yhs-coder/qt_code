#include "label.h"

#include <QDebug>
#include <QMouseEvent>
static int num = 0;
Label::Label(QWidget *parent) : QLabel{parent}
{
    // 默认为false, true设置鼠标跟踪
    this->setMouseTracking(true);
}

void Label::enterEvent(QEvent *event)
{
    // qDebug() << "enterEvent: " << ++num;
    this->setText(QString("enterEvent: %1").arg(++num));
}

void Label::leaveEvent(QEvent *event)
{
    // qDebug() << "leaveEvent: " << ++num;
    this->setText(QString("leaveEvent: %1").arg(++num));
}

void Label::mousePressEvent(QMouseEvent *ev)
{
    // button()返回点击按钮的类型Qt::MouseButton，pos() 返回相对于标签的位置，globalPos()返回相对于桌面的位置
    // qDebug() << "mousePressEvent: " << ev->button() << ev->pos() << ev->globalPos();
    if (ev->button() & Qt::LeftButton) {
        qDebug() << "左键按下： " << "x=" << ev->x() << ", y=" << ev->y();
    }
}

void Label::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() << "mouseMoveEvent: " << ev->buttons() << ev->pos() << ev->globalPos();
    if (ev->buttons() & Qt::LeftButton) {
        qDebug() << "鼠标移动中： " << "x=" << ev->x() << ", y=" << ev->y();
    }
}

void Label::mouseReleaseEvent(QMouseEvent *ev)
{
    // qDebug() << "mouseReleaseEvent: " << ev->button() << ev->pos() << ev->globalPos();
    if (ev->button() & Qt::LeftButton) {
        qDebug() << "左键释放： " << "x=" << ev->x() << ", y=" << ev->y();
    }
}
