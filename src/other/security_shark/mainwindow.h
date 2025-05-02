#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QTcpSocket>

#include "data.pb.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void append_packet(uint32_t type, QString time, QString source,
                       QString dest, QString prototol, QString len,
                       QString info);

private slots:
    void on_connect_clicked();

    void on_disconnect_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_tcp;
    QLabel *m_status;
    Protocol::ProtocolData m_p;
};
#endif  // MAINWINDOW_H
