#ifndef WIDGET_H
#define WIDGET_H

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
    void on_btnGetText_clicked();

    void on_btnSetText_clicked();

    void on_btnSetText_6_clicked();

    void on_btnGetText_6_clicked();

    void on_btnGetText_7_clicked();

    void on_pushButton_clicked();

    void on_btnEbanleWrap_clicked();

    void on_btnChangeImages_clicked();

private:
    Ui::Widget *ui;
    int index{0};
};
#endif // WIDGET_H
