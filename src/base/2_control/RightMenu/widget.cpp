#include "widget.h"

#include <QAction>
#include <QMessageBox>

#include "./ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置菜单策略
    // Qt::DefaultContextMenu: the widget's QWidget::contextMenuEvent() handler is called.
    this->setContextMenuPolicy(Qt::DefaultContextMenu);

    initMenu();
}

Widget::~Widget() { delete ui; }

void Widget::contextMenuEvent(QContextMenuEvent* event)
{
    // 在点击的位置弹出菜单
    m_pMenu->exec(QCursor::pos());
}


