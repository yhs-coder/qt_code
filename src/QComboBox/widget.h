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
    void setResult();
private slots:
    void onCboUniversityChanged(int index);
    void onCboProvinceChanged(int index);
    void onCboCityChanged(int index);

    void onLineEditChanged(QString s);

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
