#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(QWidget* parent = nullptr);

signals:

protected:
    // 重写鼠标进入事件
    void enterEvent(QEvent* event) override;
    // 重写鼠标离开事件
    void leaveEvent(QEvent* event) override;
    // 鼠标按下事件
    void mousePressEvent(QMouseEvent* ev) override;
    // 鼠标移动事件
    void mouseMoveEvent(QMouseEvent* ev) override;
    // 鼠标释放事件
    void mouseReleaseEvent(QMouseEvent* ev) override;
};

#endif  // LABEL_H
