#ifndef WINSTATE_H
#define WINSTATE_H

#include <QWidget>

namespace Ui {
class WinState;
}

class WinState : public QWidget
{
    Q_OBJECT

public:
    explicit WinState(QWidget *parent = nullptr);
    ~WinState();


private:
    Ui::WinState *ui;
};

#endif // WINSTATE_H
