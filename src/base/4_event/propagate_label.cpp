#include "propagate_label.h"

#include <QDebug>
#include <QMouseEvent>

PropagateLabel::PropagateLabel(QWidget *parent) : QLabel{parent} {}

void PropagateLabel::mousePressEvent(QMouseEvent *event)
{
    // Qt框架内部传出过来的event，默认标志位m_accept为true
    // 处理完事件后，在当前部件/控件设置是否传递给父控件！
    qDebug() << event->isAccepted();
    // 接受事件（事件到此为止，不在传递给父控件）
    // event->accept();

    // 忽略事件（事件继续传递给父控件）
    event->ignore();
    qDebug() << "PropagateLabel::mousePressEvent";
}

bool PropagateLabel::event(QEvent *e) { return false; }
