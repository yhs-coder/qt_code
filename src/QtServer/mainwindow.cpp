#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->port->setText("9999");
    setWindowTitle("服务器");
    // 创建监听的服务器对象
    m_s = new QTcpServer(this);

    // 如果有客户端连接，就发出newConnection信号
    connect(m_s, &QTcpServer::newConnection, this, [=]() {
        // 得到用于通信的套接字
        m_tcp = m_s->nextPendingConnection();

        // 标签状态转为已连接
        m_status->setPixmap(QPixmap(":/right.png").scaled(20,20));
        // 检测是否可以接收数据，当tcp对象发出readyRead信号，就进行处理
        connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
            // 一次性读取数据
            QByteArray data = m_tcp->readAll();
            ui->record->append("客户端say: " + data);
        });

        connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
            m_tcp->close();
            m_tcp->deleteLater();
            m_status->setPixmap(QPixmap(":/error.png").scaled(20,20));
        });
    });

    // 状态栏
    m_status = new QLabel;
    // 将标签设置到状态栏
    // 默认图片显示未连接
    m_status->setPixmap(QPixmap(":/error.png").scaled(20,20));
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    ui->statusbar->addWidget(m_status);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendMsg_clicked()
{
    // 把发送框中的数据以纯文本的方式提取出来
    QString msg = ui->msg->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->record->append("服务端say: " + msg);
}


void MainWindow::on_setListen_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    // 本机任意ip地址
    m_s->listen(QHostAddress::Any, port);
    // 点击后，设置按钮不可用
    ui->setListen->setDisabled(true);
}

