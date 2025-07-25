#include "paintwidget.h"

#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent) : QWidget{parent} { this->setAttribute(Qt::WA_StyledBackground, true); }

void PaintWidget::setShape(Shape shape)
{
    m_shape = shape;

    // 更新部件，调用paintEvent来处理，完成界面的刷新
    this->update();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    // 在此完成paintwidget部件的绘制
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70),
    };

    // 创建画家类的对象
    // 参数为绘图设备，this表示在当前窗口绘制
    QPainter painter(this);

    switch (m_shape) {
        case _Point:
            painter.drawPoints(points, 4);
            break;
        case _Line:
            painter.drawLine(points[0], points[2]);
            break;
    }
}
