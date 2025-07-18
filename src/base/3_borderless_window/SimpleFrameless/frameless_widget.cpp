#include "frameless_widget.h"

#include <QDebug>
#include <QEvent>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>

FramelessWidget::FramelessWidget(QWidget* parent) : QWidget(parent)
{
    // 去吃标题栏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    // 开启鼠标跟踪
    this->setMouseTracking(true);

    // 设置最小宽高
    this->setMinimumWidth(500);
    this->setMinimumHeight(300);

    // 设置背景颜色
    this->setStyleSheet("background:#303030");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    QPushButton* btn1 = new QPushButton("确定");
    QPushButton* btn2 = new QPushButton("取消");

    layout->addWidget(btn1);
    layout->addWidget(btn2);

    QString style = R"(
        QPushButton {
            background-color: rgb(64,64,64);
            font: 16px "Microsoft YaHei";
            color: rgb(200,200,200);
            border: 1px solid #707070;
            border-radius: 5px;
            padding: 5px;
        }
        QPushButton:hover {
            background-color: rgb(40,40,40);
        }
        QPushButton:pressed {
            background-color: rgb(64,64,64);
        }
    )";

    btn1->setStyleSheet(style);
    btn2->setStyleSheet(style);

    connect(btn1, &QPushButton::clicked, this, [=]() { qDebug() << btn1->text(); });
    connect(btn2, &QPushButton::clicked, this, [=]() { qDebug() << btn2->text(); });

    m_isLeftPressed = false;
}

FramelessWidget::~FramelessWidget() {}

void FramelessWidget::setCursorShape(const QPoint& cursorPoint)
{
    QRect rect = this->rect();
    // mapToGlobal() 将窗口坐标pos转换为全局屏幕坐标。
    QPoint topLeft     = mapToGlobal(rect.topLeft());
    QPoint bottomRight = mapToGlobal(rect.bottomRight());
    // int    x           = cursorPoint.x();
    // int    y           = cursorPoint.y();

    if (isOnTopLeft(cursorPoint, topLeft)) {
        m_location = TOP_LEFT;
        // Qt::SizeFDiagCursor表示一个从左上角到底右角的对角线调整光标（通常是箭头指向左上和右下）
        this->setCursor(Qt::SizeFDiagCursor);
    } else if (isOnBottomRight(cursorPoint, bottomRight)) {
        m_location = BOTTOM_RIGHT;
        setCursor(Qt::SizeFDiagCursor);
    } else if (isOnBottomLeft(cursorPoint, topLeft, bottomRight)) {
        m_location = BOTTOM_LEFT;
        // Qt::SizeBDiagCursor表示一个从右上角到左下角的对角线调整光标（通常是箭头指向右上和左下）。
        setCursor(Qt::SizeBDiagCursor);
    } else if (isOnTopRight(cursorPoint, topLeft, bottomRight)) {
        m_location = TOP_RIGHT;
        setCursor(Qt::SizeBDiagCursor);
    } else if (isOnLeft(cursorPoint, topLeft, bottomRight)) {
        m_location = LEFT;
        // Qt::SizeHorCursor：水平调整光标（左右箭头）。
        setCursor(Qt::SizeHorCursor);
    } else if (isOnRight(cursorPoint, topLeft, bottomRight)) {
        m_location = RIGHT;
        setCursor(Qt::SizeHorCursor);
    } else if (isOnTop(cursorPoint, topLeft, bottomRight)) {
        m_location = TOP;
        // Qt::SizeVerCursor：垂直调整光标（上下箭头）
        setCursor(Qt::SizeVerCursor);
    } else if (isOnBottom(cursorPoint, topLeft, bottomRight)) {
        m_location = BOTTOM;
        setCursor(Qt::SizeVerCursor);
    } else {
        m_location = CENTER;
        // Qt::ArrowCursor：标准箭头光标（默认光标）。
        setCursor(Qt::ArrowCursor);
    }
}

bool FramelessWidget::isOnTopLeft(const QPoint& point, const QPoint& topLeft) const
{
    return point.x() >= topLeft.x() && point.x() <= topLeft.x() + PADDING && point.y() >= topLeft.y()
           && point.y() <= topLeft.y() + PADDING;
}

bool FramelessWidget::isOnBottomRight(const QPoint& point, const QPoint& bottomRight) const
{
    return point.x() <= bottomRight.x() && point.x() >= bottomRight.x() - PADDING && point.y() <= bottomRight.y()
           && point.y() >= bottomRight.y() - PADDING;
}

bool FramelessWidget::isOnBottomLeft(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const
{
    return point.x() >= topLeft.x() && point.x() <= topLeft.x() + PADDING && point.y() >= bottomRight.y() - PADDING
           && point.y() <= bottomRight.y();
}

bool FramelessWidget::isOnTopRight(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const
{
    return point.x() >= bottomRight.x() - PADDING && point.x() <= bottomRight.x() && point.y() >= topLeft.y()
           && point.y() <= topLeft.y() + PADDING;
}

bool FramelessWidget::isOnLeft(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const
{
    return point.x() >= topLeft.x() && point.x() <= topLeft.x() + PADDING && point.y() > topLeft.y() + PADDING
           && point.y() < bottomRight.y() - PADDING;
}

bool FramelessWidget::isOnRight(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const
{
    return point.x() >= bottomRight.x() - PADDING && point.x() <= bottomRight.x() && point.y() > topLeft.y() + PADDING
           && point.y() < bottomRight.y() - PADDING;
}

bool FramelessWidget::isOnTop(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const
{
    return point.y() >= topLeft.y() && point.y() <= topLeft.y() + PADDING && point.x() > topLeft.x() + PADDING
           && point.x() < bottomRight.x() - PADDING;
}

bool FramelessWidget::isOnBottom(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const
{
    return point.y() >= bottomRight.y() - PADDING && point.y() <= bottomRight.y() && point.x() > topLeft.x() + PADDING
           && point.x() < bottomRight.x() - PADDING;
}

/////////////////////////////// 事件处理 ////////////////////////////////////////
void FramelessWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_isLeftPressed = false;
    }
}

void FramelessWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint globalPos   = event->globalPos();
    QRect  rect        = this->rect();
    QPoint topLeft     = mapToGlobal(rect.topLeft());
    QPoint bottomRight = mapToGlobal(rect.bottomRight());

    QRect rMove(topLeft, bottomRight);

    switch (m_location) {
        case TOP:
            // 如果不加if判断，则窗口高度达到最小高度后，会被鼠标 "向下推走"
            if (bottomRight.y() - globalPos.y() > this->minimumHeight()) {
                rMove.setY(globalPos.y());
            }
            break;
        case BOTTOM:
            rMove.setHeight(globalPos.y() - topLeft.y());
            break;
        case LEFT:
            // 如果不加if判断，则窗口高度达到最小宽度后，会被鼠标 "向右推走"
            if (bottomRight.x() - globalPos.x() > this->minimumWidth()) {
                rMove.setX(globalPos.x());
            }
            break;
        case RIGHT:
            rMove.setWidth(globalPos.x() - topLeft.x());
            break;
        case TOP_LEFT:
            // 如果不加if判断，则窗口达到最小宽高后，会被鼠标 "向右下推走"
            if (bottomRight.x() - globalPos.x() > this->minimumWidth()) {
                rMove.setX(globalPos.x());
            }
            if (bottomRight.y() - globalPos.y() > this->minimumHeight()) {
                rMove.setY(globalPos.y());
            }
            break;
        case BOTTOM_LEFT:
            // 如果不加if判断，则窗口达到最小宽高后，会被鼠标 "向右推走"
            if (bottomRight.x() - globalPos.x() > this->minimumWidth()) {
                rMove.setX(globalPos.x());
            }
            rMove.setHeight(globalPos.y() - topLeft.y());

            break;
        case TOP_RIGHT:
            rMove.setWidth(globalPos.x() - topLeft.x());
            // 如果不加if判断，则窗口达到最小宽高后，会被鼠标 "向下推走"
            if (bottomRight.y() - globalPos.y() > this->minimumHeight()) {
                rMove.setY(globalPos.y());
            }

            break;
        case BOTTOM_RIGHT:
            rMove.setWidth(globalPos.x() - topLeft.x());
            rMove.setHeight(globalPos.y() - topLeft.y());
            break;
        default:
            break;
    }
    this->setGeometry(rMove);

    // 鼠标未按下
    if (!m_isLeftPressed) {
        this->setCursorShape(globalPos);
        return;
    }

    // 鼠标载 CENTER 位置按下
    if (m_location == CENTER) {
        this->move(globalPos - m_mousePos);
        event->accept();
        return;
    }
}

void FramelessWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_isLeftPressed = true;
        // 只有载中间区域，才能移动窗口
        if (m_location == CENTER) {
            // 鼠标点击位置减去窗口（相对于桌面）坐标位置
            m_mousePos = event->globalPos() - this->frameGeometry().topLeft();
        }
    }
    if (event->button() == Qt::RightButton) {
        this->close();
    }
}
