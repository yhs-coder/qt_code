#include "text_edit.h"

#include <QApplication>
#include <QDebug>
#include <QMimeData>
#include <QWheelEvent>
// #include <QUrl>

TextEdit::TextEdit(QWidget *parent) : QTextEdit{parent}
{
    // 启动当前控件（或者窗口）的拖放功能
    this->setAcceptDrops(true);
}

void TextEdit::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dragEnterEvent";
    // 判断是正常的文件，表明用户可以在这个窗口部件上拖放对象。
    // 默认情况下,窗口部件是不接受拖动的。
    // Qt会自动改变光标来向用户说明这个窗口部件是不是有效的放下点
    // acceptProposedAction()用于明确告诉 Qt 的事件系统，当前控件接受正在进行的拖放操作。
    event->acceptProposedAction();
}

void TextEdit::dragMoveEvent(QDragMoveEvent *event) { qDebug() << "dragMoveEvent"; }

void TextEdit::dragLeaveEvent(QDragLeaveEvent *event) { qDebug() << "dragLeaveEvent"; }

void TextEdit::dropEvent(QDropEvent *event)
{
    // 当用户将文件拖放到 TextEdit 控件上并释放鼠标时，
    // 会将读取拖放的文件内容，并将其显示在 TextEdit 控件中
    qDebug() << "dropEvent";
    // mimeData() 返回一个 QMimeData 对象，其中包含了拖放的数据。
    // urls() 方法返回一个 QUrl 列表，表示拖放的文件或资源的 URL。
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }
    // 获取 URL 列表中的第一个 URL，并将其转换为本地文件路径。
    QString fileName = urls.first().toLocalFile();
    qDebug() << urls.first() << " : " << fileName;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << fileName;
        return;
    }
    // 将读取文件的全部内容，使用setPlainText()方法，设置成控件上的文本内容。
    this->setPlainText(file.readAll());
    file.close();  // 关闭文件
}

void TextEdit::wheelEvent(QWheelEvent *e)
{
    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
        // zoomIn/zoomOut可以直接修改字体大小
        // 获取滚动量
        QPoint delta = e->angleDelta();
        if (delta.y() > 0) {
            // 滚轮远离使用者（向上滚动）, 进行放大
            this->zoomIn();
        } else if (delta.y() < 0) {
            //  向下滚动，进行缩小
            this->zoomOut();  // 进行缩小
        }

    } else {
        QTextEdit::wheelEvent(e);  // 调用父类的，否则无法实现文本的上下滚动。
    }
}
