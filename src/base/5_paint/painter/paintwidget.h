#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QBrush>
#include <QPen>
#include <QWidget>

// 形状的类型
enum Shape
{
    _Point,  // 点
    _Line,   // 直线

    _Rect,         // 矩形
    _RoundedRect,  // 圆角矩形
    _Ellipse,      // 椭圆

    _Polyline,  // 折线
    _Polygon,   // 多边形

    _Arc,    // 弧
    _Pie,    // 扇形
    _Chord,  // 弦

    _Path,  // 路径

    _Text,   // 文本
    _Pixmap  // 像素图/图片
};

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setTransform(bool transform);

public slots:
    void setShape(Shape shape);
    void setAntialias(bool antialias);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Shape  m_shape;
    QPen   m_pen;
    QBrush m_brush;
    bool   m_antialias;
    bool   m_transform;
};
#endif  // PAINTWIDGET_H
