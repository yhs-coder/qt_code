#include "key_widget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QVBoxLayout>

KeyWidget::KeyWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    m_label = new QLabel(this);
    // label->setText("键盘事件");
    m_label->setFrameShape(QFrame::Box);
    m_label->setFixedSize(100, 100);
    m_label->setStyleSheet(R"(
        background-color: orange;
    )");

    verticalLayout->addWidget(m_label);

    // 设置控件（如窗口、按钮、输入框等）的焦点策略
    // 焦点策略决定了控件在什么情况下可以接收输入焦点
    // Qt::StrongFocus(最常用的焦点策略)允许控件通过鼠标点击、Tab 键切换及快捷键等操作获得焦点。
    // setFocusPolicy(Qt::StrongFocus);
    // Qt::ClickFocus
    // 控件仅在通过鼠标点击时获得焦点，不会通过 Tab 键切换获得焦点。
    setFocusPolicy(Qt::ClickFocus);
}

void KeyWidget::keyPressEvent(QKeyEvent* event)
{
    // 获取按键的类型
    switch (event->key()) {
        case Qt::Key_Return:
            qDebug() << "Enter";
            break;
        case Qt::Key_Up:
            qDebug() << "Up";
            // 控制标签块上移
            moveLabel(Qt::Key_Up);

            break;
        case Qt::Key_Down:
            qDebug() << "Down";
            // 控制标签块下移
            moveLabel(Qt::Key_Down);
            break;
        case Qt::Key_Left:
            qDebug() << "Left";
            // 控制标签块左移
            moveLabel(Qt::Key_Left);
            break;
        case Qt::Key_Right:
            qDebug() << "Right";
            // 控制标签块右移
            moveLabel(Qt::Key_Right);
            break;
        case Qt::Key_C:
            qDebug() << "C";
            break;
        case Qt::Key_V:
            qDebug() << "V";
            break;
        case Qt::Key_D:
            qDebug() << "D";
            break;
        case Qt::Key_Control:
            qDebug() << "Control";
            break;
        case Qt::Key_Shift:
            qDebug() << "Shift";
            break;
        case Qt::Key_Alt:
            qDebug() << "Alt";
            break;
        Default:
            qDebug() << "unknow!";
    }

    // 2. 两个俺就
    // modifiers()用于获取当前事件中被按下的修饰键（修饰键是指像 Shift、Ctrl、Alt 这样的键）的状态
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_C) {
        qDebug() << "Ctrl + C";
    }
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_V) {
        qDebug() << "Ctrl + V";
    }
    // 3. 三个按键
    if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_D) {
        qDebug() << "Ctrl + Shift + D";
    }
}

void KeyWidget::keyReleaseEvent(QKeyEvent* event)
{
    // 获取按键的类型
    switch (event->key()) {
        case Qt::Key_Return:
            qDebug() << "Release Enter";
            break;
        case Qt::Key_Up:
            qDebug() << "Release Up";
            break;
        case Qt::Key_Down:
            qDebug() << "Release Down";
            break;
        case Qt::Key_Left:
            qDebug() << "Release Left";
            break;
        case Qt::Key_Right:
            qDebug() << "Release  Right";
            break;
        case Qt::Key_C:
            qDebug() << "Release C";
            break;
        case Qt::Key_V:
            qDebug() << "Release V";
            break;
        case Qt::Key_D:
            qDebug() << "Release D";
            break;
        case Qt::Key_Control:
            qDebug() << "Release Control";
            break;
        case Qt::Key_Shift:
            qDebug() << "Release Shift";
            break;
        case Qt::Key_Alt:
            qDebug() << "Release Alt";
            break;
        Default:
            qDebug() << "Release unknow!";
    }
}

void KeyWidget::moveLabel(int key)
{
    // 定义每次移动的步长
    const int step = 10;

    // 根据按键方向计算目标位置
    QPoint delta;
    switch (key) {
        case Qt::Key_Up:
            delta.setY(-step);
            break;
        case Qt::Key_Down:
            delta.setY(+step);
            break;
        case Qt::Key_Left:
            delta.setX(-step);
            break;
        case Qt::Key_Right:
            delta.setX(+step);
            break;
    }

    // 计算目标位置
    QPoint targetPos = m_label->pos() + delta;

    // 调整目标位置，超出窗口边界时进行处理
    targetPos = adjustPosition(targetPos);
    // 移动标签
    m_label->move(targetPos);

    // 冗余的写法！
    // if (key == Qt::Key_Up) {
    //     m_label->move(m_label->x(), m_label->y() - 10);
    //     if (m_label->y() <= -(m_label->height())) {
    //         m_label->move(m_label->x(), this->height());
    //     }
    // }

    // if (key == Qt::Key_Down) {
    //     m_label->move(m_label->x(), m_label->y() + 10);
    //     if (m_label->y() >= (this->height())) {
    //         m_label->move(m_label->x(), -(m_label->height()));
    //     }
    // }

    // if (key == Qt::Key_Left) {
    //     m_label->move(m_label->x() - 10, m_label->y());
    //     if (m_label->x() <= -(m_label->width())) {
    //         m_label->move(this->width(), m_label->y());
    //     }
    // }
    // if (key == Qt::Key_Right) {
    //     m_label->move(m_label->x() + 10, m_label->y());
    //     if (m_label->x() >= this->width()) {
    //         m_label->move(-(m_label->width()), m_label->y());
    //     }
    // }
}

QPoint KeyWidget::adjustPosition(QPoint pos) const
{
    // 获取窗口和标签的大小
    int windowWidth  = this->width();
    int windowHeight = this->height();
    int labelWidth   = m_label->width();
    int labelHeight  = m_label->height();

    // 调整 x 坐标
    if (pos.x() <= -labelWidth) {
        pos.setX(windowWidth);
    } else if (pos.x() >= windowWidth) {
        pos.setX(-labelWidth);
    }

    // 调整 y 坐标
    if (pos.y() <= -labelHeight) {
        pos.setY(windowHeight);
    } else if (pos.y() >= windowHeight) {
        pos.setY(-labelHeight);
    }

    return pos;
}
