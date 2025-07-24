#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

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

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    // 初始化界面
    void initUI();

private:
    Ui::Widget *ui;
};
#endif  // WIDGET_H
