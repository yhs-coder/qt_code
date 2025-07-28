#ifndef WIDGET_H
#define WIDGET_H

// #include <QLabel>
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

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

    // 绘制温度曲线
    void paintTemperatureCurve(QWidget* label, const int* temp, const QColor& color);

    // 绘制高低温曲线
    void paintHigh();
    void paintLow();

    // 更新高低温
    void updateTemp();

private:
    Ui::Widget* ui;
    // QLabel*     m_lblHigh;
    // QLabel*     m_lblLow;

    int m_highTemp[7] = {0};
    int m_lowTemp[7]  = {0};
};
#endif  // WIDGET_H
