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
    QString getRGBValue();    // 返回颜色值
    void setBackgroupColor(); // 更新背景颜色

private slots:
    void on_hsRed_valueChanged(int value);
    void on_hsGreen_valueChanged(int value);
    void on_hsBlue_valueChanged(int value);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
