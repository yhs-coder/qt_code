#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>

#include "childthread.h"

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
    void on_btnSet_clicked();

    void on_btnUpdate_clicked();

    void showInfo(Score s);
    void showInfo2(string name, int id);
    // void showInfo2(string name, int age);
    void onIndex(int index);
    void onIndexStr(const QString &index);

private:
    Ui::Widget *ui;
};
#endif  // WIDGET_H
