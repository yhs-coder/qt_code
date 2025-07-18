#ifndef FRAMELESS_WIDGET_H
#define FRAMELESS_WIDGET_H

#include <QWidget>
// 定义一个间距
#define PADDING 5

enum Location
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    CENTER
};

class FramelessWidget : public QWidget
{
    Q_OBJECT

public:
    FramelessWidget(QWidget* parent = nullptr);
    ~FramelessWidget();

private:
    // 设置鼠标形状
    void setCursorShape(const QPoint& cursorPoint);

    // @brief: 判断鼠标是否在左上角
    bool isOnTopLeft(const QPoint& point, const QPoint& topLeft) const;

    // 判断鼠标是否在右下角
    bool isOnBottomRight(const QPoint& point, const QPoint& bottomRight) const;

    // 判断鼠标是否在左下角
    bool isOnBottomLeft(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const;

    // 判断鼠标是否在右上角
    bool isOnTopRight(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const;

    // 判断鼠标是否在左边
    bool isOnLeft(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const;

    // 判断鼠标是否在右边
    bool isOnRight(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const;

    // 判断鼠标是否在顶部
    bool isOnTop(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const;

    // 判断鼠标是否在底部
    bool isOnBottom(const QPoint& point, const QPoint& topLeft, const QPoint& bottomRight) const;

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    bool     m_isLeftPressed;  // 鼠标左键是否按下
    QPoint   m_mousePos;       // 记录鼠标按下的位置
    Location m_location;       // 移动位置
};
#endif  // FRAMELESS_WIDGET_H
