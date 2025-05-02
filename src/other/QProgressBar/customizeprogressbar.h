#ifndef CUSTOMIZEPROGRESSBAR_H
#define CUSTOMIZEPROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>
namespace Ui {
class CustomizeProgressBar;
}

class CustomizeProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit CustomizeProgressBar(QWidget *parent = nullptr);
    ~CustomizeProgressBar();

private:
    Ui::CustomizeProgressBar *ui;
    void paintEvent(QPaintEvent *);
};

#endif // CUSTOMIZEPROGRESSBAR_H
