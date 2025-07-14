#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QTextEdit>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget* parent = nullptr);

protected:
    // 重写拖动事件
    //  拖动文件进入到窗口/控件中时
    void dragEnterEvent(QDragEnterEvent* event) override;
    // ​ 拖动文件离开窗口/控件
    void dragMoveEvent(QDragMoveEvent* event) override;
    // 拖动文件在窗口/控件中移动
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    // 移动文件在窗口/控件中释放
    void dropEvent(QDropEvent* event) override;

    // 重写鼠标滚轮滚动事件，实现鼠标滚轮滚动放大字体
    void wheelEvent(QWheelEvent* e) override;
};

#endif  // TEXT_EDIT_H
