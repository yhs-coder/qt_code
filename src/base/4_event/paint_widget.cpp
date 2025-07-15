#include "paint_widget.h"

#include <QDebug>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QVBoxLayout>

// 温度曲线相关的宏
#define PADDING 50
#define INCREMENT 8       // 温度曲线像素增量
#define POINT_RADIUS 4    // 曲线描点的大小
#define TEXT_OFFSET_X 12  // 温度文本相对于点的偏移
#define TEXT_OFFSET_Y 10  // 温度文本相对于点的偏移

PaintWidget::PaintWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    // 添加一个label，用于绘制高温曲线
    m_lblHigh = new QLabel(this);
    m_lblHigh->setText("");
    m_lblHigh->setFrameShape(QFrame::Box);

    // 添加一个label，用于绘制低温曲线
    m_lblLow = new QLabel(this);
    m_lblLow->setText("");
    m_lblLow->setFrameShape(QFrame::Box);

    verticalLayout->addWidget(m_lblHigh);
    verticalLayout->addWidget(m_lblLow);

    // 随即生成温度
    updateTemp();

    // 安装事件过滤器
    m_lblHigh->installEventFilter(this);
    m_lblLow->installEventFilter(this);
}

bool PaintWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::Paint) {
        if (watched == m_lblHigh) {
            qDebug() << "paint m_lblHigh";
            paintHigh();
        }
        if (watched == m_lblLow) {
            qDebug() << "paint m_lblLow";
            paintLow();
        }
    } else if (event->type() == QEvent::MouseButtonDblClick) {
        updateTemp();
    }

    return QWidget::eventFilter(watched, event);
}

void PaintWidget::paintTemperatureCurve(QWidget* label, const int* temp, const QColor& color)
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

void PaintWidget::paintHigh()
{
#if 1
    paintTemperatureCurve(m_lblHigh, m_highTemp, QColor(255, 0, 0));

#else
    QPainter painter(m_lblHigh);
    // 抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 1. 计算x轴坐标
    int pointX[7] = {0};
    for (int i = 0; i < 7; i++) {
        pointX[i] = m_lblHigh->pos().x() + PADDING + (m_lblHigh->width() - PADDING * 2) / 6 * i;
    }

    // 2. 计算温度平均值
    int tempSum     = 0;
    int tempAverage = 0;
    for (int i = 0; i < 7; i++) {
        tempSum += m_highTemp[i];
    }

    tempAverage = tempSum / 7;

    // 3. 计算y轴坐标
    int pointY[7] = {0};
    // 将标签分为一半
    int yCenter   = m_lblHigh->height() / 2;
    int increment = m_lblHigh->height() / 20;

    for (int i = 0; i < 7; i++) {
        // 在窗口中，y轴是向下增长
        // 当温度比平均温度高，温度向上增长，但y轴向上减少
        pointY[i] = yCenter + (-(m_highTemp[i] - tempAverage) * increment);
    }

    // 4. 开始绘制
    // 初始化画笔
    QPen pen = painter.pen();
    pen.setWidth(3);                  // 设置画笔宽度为3
    pen.setColor(QColor(255, 0, 0));  // 设置画笔颜色

    painter.setPen(pen);
    painter.setBrush(QColor(255, 0, 0));  // 设置画刷颜色
    painter.setFont(QFont("Microsoft YaHei", 14));

    // 画点、写文本
    for (int i = 0; i < 7; i++) {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_RADIUS, POINT_RADIUS);
        painter.drawText(QPoint(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y), QString::number(m_highTemp[i]) + "°");
    }
    qDebug() << "draw here...";

    // 绘制曲线
    for (int i = 0; i < 6; i++) {
        if (i == 0) {
            pen.setStyle(Qt::DotLine);  // 虚线
            painter.setPen(pen);
        } else {
            pen.setStyle(Qt::SolidLine);  // 实线
            painter.setPen(pen);
        }
        painter.drawLine(pointX[i], pointY[i], pointX[i + 1], pointY[i + 1]);
    }
#endif
}

void PaintWidget::paintLow() { paintTemperatureCurve(m_lblLow, m_lowTemp, QColor(0, 0, 255)); }

void PaintWidget::updateTemp()
{
    for (int i = 0; i < 7; i++) {
        // 生成一个32位随机数并返回。
        m_highTemp[i] = 20 + QRandomGenerator::global()->generate() % 10;
        m_lowTemp[i]  = -5 + QRandomGenerator::global()->generate() % 10;
    }

    // 更新标签控件，重绘标签，框架发送 QEvent::Paint 事件给标签
    m_lblHigh->update();
    m_lblLow->update();
}
