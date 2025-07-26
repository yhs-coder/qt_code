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
    // 设置画笔
    painter.setPen(m_pen);
    painter.setBrush(m_brush);

    // QRect(int left, int top, int width, int height) noexcept;
    // 在左上角的顶点(10,20)
    QRect rect(10, 20, 80, 60);

    QRect rect2(10, 10, 80, 80);

    // Qt 为了支持“半度”精度，把 1° 定义成 16 个单位
    // 30° 要写成 30*16
    // 90° 要写成 90*16
    int startAngle = 0 * 16;
    int arcLength  = 90 * 16;

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
                case _Polyline:  // 多段线
                    painter.drawPolyline(points, 4);
                    break;
                case _Polygon:  // 多边形
                    painter.drawPolygon(points, 4);
                    break;
                case _Rect:  // 矩形
                    painter.drawRect(rect);
                    break;
                case _RoundedRect:
                    // // 第四个参数是一个枚举类型，可指定为：AbsoluteSize 或 RelativeSize
                    // 当指定为AbsoluteSize，则2，3参数为圆角大小
                    // 当指定为RelativeSize，则2，3参数为圆角百分比
                    painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
                    break;
                case _Ellipse:  // 园、椭圆
                    // painter.drawEllipse(10, 20, 80, 60);  // 指定矩形的左上角以及宽高
                    // painter.drawEllipse(QPoint(50, 50), 40, 30);  // 指定中心点和rx ry
                    // painter.drawEllipse(rect);  					// 直接指定指定矩形
                    painter.drawEllipse(QPoint(50, 50), 40, 40);  // 圆
                    break;
                case _Arc:  // 圆弧
                    // 将80*80的矩形当成外接矩形，在该矩形中画圆弧
                    // startAngle = 30 * 16表示起始角度，是从矩形中心向右为0°，逆时针为正方向
                    // arcLength = 120*16 表示扫过角度：从起始角再逆时针转 120°，因此弧从 30° 画到 150°。
                    painter.drawRect(rect2);
                    painter.drawArc(rect2, startAngle, arcLength);
                    break;
                case _Pie:  // 饼图
                    painter.drawRect(rect2);
                    painter.drawPie(rect2, startAngle, arcLength);
                    break;
                case _Chord:  // 弦图
                    painter.drawRect(rect2);
                    painter.drawChord(rect2, startAngle, arcLength);
                    break;
            }
            // 恢复painter之前的状态 （painter状态出栈）
            painter.restore();
        }
    }
}

void PaintWidget::setPen(const QPen &pen)
{
    m_pen = pen;
    update();
}

void PaintWidget::setBrush(const QBrush &brush)
{
    m_brush = brush;
    update();
}
