#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Qpen>

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

private:
    // 初始化界面
    void initUI();

private slots:
    void shapeChange();
    void penChange();

    void onBbtnPenColorClicked();
    void onBtnBrushColorClicked();
    void brushChange();
    void antialiasChange();
    void transformChange();

private:
    Ui::Widget *ui;
};
#endif  // WIDGET_H
