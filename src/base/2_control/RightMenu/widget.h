#ifndef WIDGET_H
#define WIDGET_H

#include <QMenu>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

    // 菜单事件
    void contextMenuEvent(QContextMenuEvent* event) override;

    void initMenu();

private:
    Ui::Widget* ui;
    QMenu*      m_pMenu = nullptr;
};
#endif  // WIDGET_H
