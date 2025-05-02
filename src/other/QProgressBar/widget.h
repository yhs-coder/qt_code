#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "customizeprogressbar.h"

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
    void onBtnDownloadClicked();
    void onDownloadTimeout();
    void onBtnCopyClicked();
    void onCopyTimeout();

private:
    Ui::Widget *ui;

    QTimer* mTimerDownload; // 开始下载定时器
    QTimer* mTimerCopy;     // 开始拷贝定时器

    CustomizeProgressBar* bar;
};
#endif // WIDGET_H
