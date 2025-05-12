#ifndef WIDGET_H
#define WIDGET_H

#include <QListWidget>
#include <QMenu>
#include <QVBoxLayout>
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
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_PopupRightMenu(const QPoint &pos);

private:
    void initRightMenu();
    void initTabWidget();

private:
    Ui::Widget  *ui;
    QMenu       *m_pRightMenu   = nullptr;
    QWidget     *m_subWidget    = nullptr;
    QVBoxLayout *m_pMainVLayout = nullptr;
    QListWidget *m_pListWidget  = nullptr;
};
#endif  // WIDGET_H
