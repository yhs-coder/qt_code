#include "widget.h"

#include <QPainter>
#include <QRandomGenerator>

#include "./ui_widget.h"

// 温度曲线相关的宏
#define PADDING 50
#define INCREMENT 8       // 温度曲线像素增量
#define POINT_RADIUS 4    // 曲线描点的大小
#define TEXT_OFFSET_X 12  // 温度文本相对于点的偏移
#define TEXT_OFFSET_Y 10  // 温度文本相对于点的偏移

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 安装事件过滤器
    ui->lblHigh->installEventFilter(this);
    ui->lblLow->installEventFilter(this);

    updateTemp();
}

Widget::~Widget() { delete ui; }

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Paint) {
        if (watched == ui->lblHigh) {
            paintHigh();
        }
        if (watched == ui->lblLow) {
            paintLow();
        }
    } else if (event->type() == QEvent::MouseButtonDblClick) {
        updateTemp();
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::paintTemperatureCurve(QWidget *label, const int *temp, const QColor &color)
{
    QPainter painter(label);
    // 抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 1. 计算x轴坐标
    int pointX[7] = {0};
    for (int i = 0; i < 7; i++) {
        pointX[i] = label->pos().x() + PADDING + (label->width() - PADDING * 2) / 6 * i;
    }

    // 2. 计算温度平均值
    int tempSum = 0;
    for (int i = 0; i < 7; i++) {
        tempSum += temp[i];
    }
    int tempAverage = tempSum / 7;

    // 3. 计算y轴坐标
    int pointY[7] = {0};
    int yCenter   = label->height() / 2;
    int increment = label->height() / 20;

    for (int i = 0; i < 7; i++) {
        pointY[i] = yCenter + (-(temp[i] - tempAverage) * increment);
    }
    // 4. 开始绘制
    // 初始化画笔
    QPen pen = painter.pen();
    pen.setWidth(3);      // 设置画笔宽度为3
    pen.setColor(color);  // 设置画笔颜色
    painter.setPen(pen);
    painter.setBrush(color);  // 设置画刷颜色
    painter.setFont(QFont("Microsoft YaHei", 14));

    // 画点、写文本
    for (int i = 0; i < 7; i++) {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_RADIUS, POINT_RADIUS);
        painter.drawText(QPoint(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y), QString::number(temp[i]) + "°");
    }
    // 绘制曲线
    for (int i = 0; i < 6; i++) {
        if (i == 0) {
            pen.setStyle(Qt::DotLine);  // 虚线
        } else {
            pen.setStyle(Qt::SolidLine);  // 实线
        }
        painter.setPen(pen);
        painter.drawLine(pointX[i], pointY[i], pointX[i + 1], pointY[i + 1]);
    }
}

void Widget::paintHigh() { paintTemperatureCurve(ui->lblHigh, m_highTemp, QColor(255, 170, 0)); }

void Widget::paintLow() { paintTemperatureCurve(ui->lblLow, m_lowTemp, QColor(0, 255, 255)); }

void Widget::updateTemp()
{
    for (int i = 0; i < 7; i++) {
        // 生成一个32位随机数并返回。
        m_highTemp[i] = 20 + QRandomGenerator::global()->generate() % 10;
        m_lowTemp[i]  = -5 + QRandomGenerator::global()->generate() % 10;
    }

    // 更新标签控件，重绘标签，框架发送 QEvent::Paint 事件给标签
    ui->lblHigh->update();
    ui->lblLow->update();
}
