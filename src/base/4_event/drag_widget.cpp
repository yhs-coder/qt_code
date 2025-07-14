#include "drag_widget.h"

#include <QLabel>
#include <QVBoxLayout>

#include "text_edit.h"

DragWidget::DragWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(5, 5, 5, 5);

    // 添加一个TextEdit
    TextEdit* textEdit = new TextEdit(this);
    textEdit->setPlaceholderText("支持文件以拖放的方式，来打开文件");

    verticalLayout->addWidget(textEdit);
}
