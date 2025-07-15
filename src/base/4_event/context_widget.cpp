#include "context_widget.h"

#include <QContextMenuEvent>
#include <QDebug>
#include <QLabel>
#include <QMenu>
#include <QVBoxLayout>

ContextWidget::ContextWidget(QWidget* parent) : QWidget{parent}
{
    m_cut     = new QAction("剪切(T)", this);
    m_copy    = new QAction("复制(C)", this);
    m_paste   = new QAction("粘贴(P)", this);
    m_toUpper = new QAction("转成大写(U)", this);
    m_toLower = new QAction("转成小写(L)", this);
    m_hide    = new QAction("隐藏行", this);

    connect(m_cut, &QAction::triggered, this, &ContextWidget::slotAction);
    connect(m_copy, &QAction::triggered, this, &ContextWidget::slotAction);
    connect(m_paste, &QAction::triggered, this, &ContextWidget::slotAction);
    connect(m_toUpper, &QAction::triggered, this, &ContextWidget::slotAction);
    connect(m_toLower, &QAction::triggered, this, &ContextWidget::slotAction);
    connect(m_hide, &QAction::triggered, this, &ContextWidget::slotAction);
}

void ContextWidget::slotAction()
{
    // sender()返回指向发出信号对象的指针
    QAction* act = (QAction*)sender();
#if 0
   if ( act == m_cut ) {
        qDebug() << "slot_cut";
    }
#endif
    qDebug() << act->text();
}

void ContextWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu* menu = new QMenu();
    menu->setFixedWidth(200);
    menu->addAction(m_cut);
    menu->addAction(m_copy);
    menu->addAction(m_paste);
    menu->addSeparator();
    menu->addAction(m_toUpper);
    menu->addAction(m_toLower);
    menu->addSeparator();
    menu->addAction(m_hide);
    menu->exec(event->globalPos());
    delete menu;
}
