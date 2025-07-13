#ifndef KEY_WIDGET_H
#define KEY_WIDGET_H

#include <QLabel>
#include <QWidget>

class KeyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeyWidget(QWidget* parent = nullptr);

private:
    // 键盘按下
    void keyPressEvent(QKeyEvent* event) override;
    // 键盘释放
    void keyReleaseEvent(QKeyEvent* event) override;

    // 移动标签
    void moveLabel(int key);

    // 标签越过边界的处理
    QPoint adjustPosition(QPoint pos) const;

private:
    QLabel* m_label;
};

#endif  // KEY_WIDGET_H
