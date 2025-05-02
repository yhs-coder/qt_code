#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->port->setText("9999");
    ui->ip->setText("192.168.19.222");
    setWindowTitle("客户端");
    ui->disconnect->setDisabled(true);
    // 创建监听的服务器对象
    m_tcp = new QTcpSocket(this);

    connect(m_tcp, &QTcpSocket::readyRead, this, [=]() {
        // 一次性读取数据
        QByteArray data = m_tcp->readAll();
        if (data.isEmpty()) {
            ui->record->append("接收到空数据包");
            return;
        }
        if (!m_p.ParseFromString(data.toStdString())) {
            ui->record->append("反序列化失败！");
            return;
        }

        // 反序列化数据
        // m_p.ParseFromString(data.toStdString());
        // ui->record->append("服务端say: " + data);

        // 这里不应该直接使用QByteArray的toStdString，因为QByteArray可能包含二进制数据
        // QString::fromUtf8是安全的选择，它会自动处理UTF-8编码的字符串
        QString displayData = QString::fromUtf8(data);
        // 输出服务端数据
        // ui->record->append("服务端say: " + displayData);
        ui->record->append("反序列化数据");

        std::string macAddress = m_p.eth().dst();
        QString qMacAddress = QString::fromStdString(macAddress);
        // qMacAddress.replace(":", "");
        switch (m_p.type()) {
            case 1: {
                ui->record->append("协议类型: ethernetII");
                ui->record->append("目标mac地址: " + qMacAddress);
                macAddress = m_p.eth().src();
                qMacAddress = QString::fromStdString(macAddress);
                ui->record->append("源mac地址: " + qMacAddress);
            } break;
            case 2: {
                ui->record->append("协议类型: arp");
                ui->record->append("hardware type: " +
                                   QString::number(m_p.arp().hardware_type()));
                ui->record->append("hardware size: " +
                                   QString::number(m_p.arp().hardware_size()));
                ui->record->append("protocol type: " +
                                   QString::number(m_p.arp().protocol_type()));
                ui->record->append("protocol size: " +
                                   QString::number(m_p.arp().protocol_size()));
                ui->record->append("op type: " +
                                   QString::number(m_p.arp().op_type()));
                ui->record->append(
                    "目标MAC地址: " +
                    QString::fromStdString(m_p.arp().target_mac()));
                ui->record->append("目标IP地址: " + QString::fromStdString(
                                                        m_p.arp().target_ip()));
                ui->record->append("源MAC地址: " + QString::fromStdString(
                                                       m_p.arp().source_mac()));
                ui->record->append("源IP地址: " + QString::fromStdString(
                                                      m_p.arp().source_ip()));
            } break;
            case 3: {
                ui->record->append("协议类型: ipv4");
                ui->record->append("version: " +
                                   QString::number(m_p.ip().version()));
                ui->record->append("header len: " +
                                   QString::number(m_p.ip().header_len()));
                ui->record->append("service type: " +
                                   QString::number(m_p.ip().service_type()));
                ui->record->append("total len: " +
                                   QString::number(m_p.ip().total_len()));
                ui->record->append("identification: " +
                                   QString::number(m_p.ip().identification()));
                ui->record->append("flags: " +
                                   QString::number(m_p.ip().flags()));
                ui->record->append("fragment offset: " +
                                   QString::number(m_p.ip().fragment_offset()));
                ui->record->append("ttl: " + QString::number(m_p.ip().ttl()));
                ui->record->append("protocol: " +
                                   QString::number(m_p.ip().protocol()));
                ui->record->append("checksum: " +
                                   QString::number(m_p.ip().checksum()));
                ui->record->append("源IP地址: " + QString::fromStdString(
                                                      m_p.ip().source_ip()));
                ui->record->append("目标IP地址: " + QString::fromStdString(
                                                        m_p.ip().target_ip()));
            } break;
            case 4: {
                ui->record->append("协议类型: tcp");
                ui->record->append("source port: " +
                                   QString::number(m_p.tcp().source_port()));
                ui->record->append("target_port: " +
                                   QString::number(m_p.tcp().target_port()));
                ui->record->append("seq num: " +
                                   QString::number(m_p.tcp().seq_num()));
                ui->record->append("ack num: " +
                                   QString::number(m_p.tcp().ack_num()));
                ui->record->append("header len: " +
                                   QString::number(m_p.tcp().header_len()));
                ui->record->append("reserve: " +
                                   QString::number(m_p.tcp().reserve()));
                ui->record->append("urg: " + QString::number(m_p.tcp().urg()));
                ui->record->append("syn: " + QString::number(m_p.tcp().syn()));
                ui->record->append("ack: " + QString::number(m_p.tcp().ack()));
                ui->record->append("window size: " +
                                   QString::number(m_p.tcp().window()));
                ui->record->append("checksum: " +
                                   QString::number(m_p.tcp().checksum()));
                ui->record->append("urgent pointer: " +
                                   QString::number(m_p.tcp().urgent_pointer()));
                ui->record->append("flags: " +
                                   QString::number(m_p.tcp().flags()));
            } break;
            case 5: {
                ui->record->append("协议类型: udp");
                ui->record->append("checksum: " +
                                   QString::number(m_p.udp().check_sum()));
                ui->record->append("total size: " +
                                   QString::number(m_p.udp().total_size()));
                ui->record->append("source port: " +
                                   QString::number(m_p.udp().source_port()));
                ui->record->append("target_port: " +
                                   QString::number(m_p.udp().target_port()));

            } break;
            case 7: {
                ui->record->append(
                    "http method: " +
                    QString::fromStdString(m_p.http_request().method()));
                ui->record->append(
                    "http path: " +
                    QString::fromStdString(m_p.http_request().path()));
                ui->record->append(
                    "http version: " +
                    QString::fromStdString(m_p.http_request().http_version()));
                ui->record->append(
                    "http body: " +
                    QString::fromStdString(m_p.http_request().body()));
                for (const auto& pair : m_p.http_request().headers()) {
                    //                    ui->record->append(QString::fromStdString(pair.first)
                    //                    +
                    //                                       ": " +
                    //                                       QString::fromStdString(pair.second));
                    QString phrase = QString::fromStdString(pair.second);
                    phrase.replace("\n", "");  // 移除所有换行符
                    ui->record->append(QString::fromStdString(pair.first) +
                                       ": " + phrase);
                }
            } break;
            case 8: {
                ui->record->append(
                    "http version: " +
                    QString::fromStdString(m_p.http_response().http_version()));
                ui->record->append(
                    "http status code: " +
                    QString::fromStdString(m_p.http_response().status_code()));
                ui->record->append(
                    "http phrase: " +
                    QString::fromStdString(m_p.http_response().phrase()));

                for (const auto& pair : m_p.http_response().headers()) {
                    QString phrase = QString::fromStdString(pair.second);
                    phrase.replace("\n", "");  // 移除所有换行符
                    ui->record->append(QString::fromStdString(pair.first) +
                                       ": " + phrase);
                }
            } break;
            default:
                break;
        }
        // 如果dst()返回的是二进制数据，您需要将其转换为QString
        // 这里需要根据您的Protobuf定义和实际数据格式来进行转换

        // ui->record->append("目标mac地址:"+ m_p.eth().dst());
        //        ui->record->append(QString::fromStdString("目标mac地址: " +
        //        m_p.eth().dst()));
        //        ui->record->append(QString::fromStdString("源mac地址: " +
        //        m_p.eth().dst()));
        // ui->record->append("反序列化数据");
    });
    connect(m_tcp, &QTcpSocket::disconnected, this, [=]() {
        m_tcp->close();
        // m_tcp->deleteLater(); // delete m_tcp
        m_status->setPixmap(QPixmap(":/error.png").scaled(20, 20));
        ui->record->append("服务端已经和客户端断开了连接....");
        ui->connect->setDisabled(false);
        ui->disconnect->setEnabled(false);
    });

    connect(m_tcp, &QTcpSocket::connected, this, [=]() {
        m_status->setPixmap(QPixmap(":/right.png").scaled(20, 20));
        ui->record->append("已经成功连接到服务器....");
        ui->connect->setDisabled(true);
        ui->disconnect->setEnabled(true);
    });

    // 状态栏
    m_status = new QLabel;
    // 将标签设置到状态栏
    // 默认图片显示未连接
    m_status->setPixmap(QPixmap(":/error.png").scaled(20, 20));
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    ui->statusbar->addWidget(m_status);

    Protocol::ProtocolData p;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_sendMsg_clicked() {
    // 把发送框中的数据以纯文本的方式提取出来
    QString msg = ui->msg->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->record->append("客户端say: " + msg);
}

void MainWindow::on_connect_clicked() {
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    m_tcp->connectToHost(QHostAddress(ip), port);
}

void MainWindow::on_disconnect_clicked() {
    m_tcp->close();
    ui->connect->setDisabled(false);
    ui->disconnect->setEnabled(false);
}
