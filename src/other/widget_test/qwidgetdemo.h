#ifndef QWIDGETDEMO_H
#define QWIDGETDEMO_H

#include <QWidget>

namespace Ui {
class QWidgetDemo;
}

class QWidgetDemo : public QWidget
{
    Q_OBJECT

public:
    explicit QWidgetDemo(QWidget *parent = nullptr);
    ~QWidgetDemo();

private slots:
    void on_btnGetSize_clicked();

    void on_btnSetSize_clicked();

    void on_btnSetFixedSize_clicked();

    void on_btnSetMaxSize_clicked();

    void on_btnSetMinSize_clicked();

    void on_btnMove_clicked();

    void on_btnSetTitle_clicked();

    void on_btnSetIcon_clicked();

private:
    Ui::QWidgetDemo *ui;
};

#endif // QWIDGETDEMO_H
