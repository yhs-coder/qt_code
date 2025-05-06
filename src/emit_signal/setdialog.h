#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>

namespace Ui {
class SetDialog;
}

class SetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDialog(QWidget *parent = nullptr);
    ~SetDialog();

signals:
    void sig_addOne(int num);

private slots:
    void on_btnAdd_clicked();

private:
    Ui::SetDialog *ui;
};

#endif  // SETDIALOG_H
