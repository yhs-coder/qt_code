#ifndef PRESS_MOVE_RELEASE_WIDGET_H
#define PRESS_MOVE_RELEASE_WIDGET_H
#include <QLabel>
#include <QWidget>
class PressMoveReleaseWidget : public QWidget
{
    Q_OBJECT
public:
    PressMoveReleaseWidget(QWidget* parent = nullptr);

    // 标签块移动时的边界处理
    void boundaryProcess(QPoint& dstPos);

private:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    QLabel*  m_label;
    QWidget* m_widget;
    QPoint   m_pressPos;  // 鼠标按下的位置（相对于桌面左上角的点）
    QPoint   m_wndPos;    // 标签的位置,相对于当前控件窗口top-left
};

#endif  // PRESS_MOVE_RELEASE_WIDGET_H
