#include "propagate_label.h"

#include <QDebug>
#include <QMouseEvent>

PropagateLabel::PropagateLabel(QWidget *parent) : QLabel{parent} {}

void PropagateLabel::mousePressEvent(QMouseEvent *event)
{
    // Qt框架内部传出过来的event，默认标志位m_accept为true
    // 处理完事件后，在当前部件/控件设置是否传递给父控件！
    // qDebug() << event->isAccepted();
    // 接受事件（事件到此为止，不在传递给父控件）
    // event->accept();

    // 忽略事件（事件继续传递给父控件）
    event->ignore();
    qDebug() << "PropagateLabel::mousePressEvent";
}

bool PropagateLabel::event(QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress) {
        qDebug() << "PropagateLabel::event";
        // 如果直接返回true,表示事件被识别，传递到此为止，同时也不会调用PropagateLabel的事件处理函数
        // return true;

        // 如果直接返回false,表示事件没有被识别，会接着传递
        // 由于没有调用父类的event()函数，不会将事件分发给PropagateLabel的mousePressEvent()
        // 而是直接将事件传递给父控件的mousePressEvent()
        // return false;
    }
    // 调用父类的event函数
    return QLabel::event(e);
}
