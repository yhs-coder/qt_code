#ifndef PAINT_WIDGET_H
#define PAINT_WIDGET_H

#include <QLabel>
#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    // 绘制高低温曲线
    void paintHigh();
    void paintLow();

    // 更新高低温
    void updateTemp();

private:
    QLabel* m_lblHigh;
    QLabel* m_lblLow;

    int m_highTemp[7] = {0};
    int m_lowTemp[7]  = {0};
};

#endif  // PAINT_WIDGET_H
