#include "customizeprogressbar.h"
#include "ui_customizeprogressbar.h"
#include <QPainter>

CustomizeProgressBar::CustomizeProgressBar(QWidget *parent)
    : QProgressBar(parent)
    , ui(new Ui::CustomizeProgressBar)
{
    ui->setupUi(this);
    setMinimum(0);
    setMaximum(100);
    setValue(0);
}

CustomizeProgressBar::~CustomizeProgressBar()
{
    delete ui;
}

void CustomizeProgressBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect rect = QRect(0, 0, width(), height()/2);
    QRect textRect = QRect(0, height()/2, width(), height()/2);

    const double k = (double)(value() - minimum()) / (maximum()-minimum());
    int x = (int)(rect.width() * k);
    QRect fillRect = rect.adjusted(0, 0, x-rect.width(), 0);

    QString valueStr = QString("%1%").arg(QString::number(value()));
    QPixmap buttomMap = QPixmap(":/resource/radius_back.png");
    QPixmap fillMap = QPixmap(":/resource/radius_front.png");

    //画进度条
    p.drawPixmap(rect, buttomMap);
    p.drawPixmap(fillRect, fillMap, fillRect);

    //画文字
    QFont f = QFont("Microsoft YaHei", 15, QFont::Bold);
    p.setFont(f);
    p.setPen(QColor("#555555"));
    p.drawText(textRect, Qt::AlignCenter, valueStr);
}

int A()
{
    char array[5] = {0};

}
