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

    // 整个paintwidget窗口填满绘制的形状
    for (int x = 0; x < this->width(); x += 100) {
        for (int y = 0; y < this->height(); y += 100) {
            // 保留当前painter状态 （当前painter状态入栈））
            // 即（0，0)，（0，100）
            //  (100，0)，(100,100)
            painter.save();
            // 按给定的偏移量转换坐标系
            painter.translate(x, y);
            switch (m_shape) {
                case _Point:  // 点
                    painter.drawPoints(points, 4);
                    break;
                case _Line:  // 线
                    painter.drawLine(points[0], points[2]);
                    break;
            }
            // 恢复painter之前的状态 （painter状态出栈）
            painter.restore();
        }
    }
}
