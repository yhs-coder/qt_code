#ifndef WIDGET_H
#define WIDGET_H

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
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnEchoNormal_clicked();

    void on_btnEchoPassword_clicked();

    void on_btnEchoNoEcho_clicked();

    void on_btnEchoPasswordEchoOnEdit_clicked();

    void on_btnEchoPrint_clicked();

    void on_btnAlignLeft_clicked();

    void on_btnAlignCenter_clicked();

    void on_btnAlignRight_clicked();

    void on_btnAccessReadWrite_clicked();

    void on_btnAccessReadOnly_clicked();

    void on_btnAccessDisabled_clicked();

    void on_btnAccessEnabled_clicked();

    void on_btnMaskNone_clicked();

    void on_btnMaskPhone_clicked();

    void on_btnMaskLicense_clicked();

    void on_leAdd1_textChanged(const QString &arg1);

    void on_leAdd2_textChanged(const QString &arg1);

    void on_leSub1_editingFinished();

    void on_leSub2_editingFinished();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
