#include "mainwindow.h"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->port->setText("9999");
    ui->ip->setText("192.168.19.222");
    setWindowTitle("流量分析-shark");
    // 断开连接按钮默认不可用
    ui->disconnect->setDisabled(true);

    // 状态栏
    m_status = new QLabel;
    // 将标签设置到状态栏
    // 默认图片显示未连接
    m_status->setPixmap(QPixmap(":/false.png").scaled(20, 20));
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    ui->statusbar->addWidget(m_status);

    // 创建监听的服务器对象
    m_tcp = new QTcpSocket(this);

    connect(m_tcp, &QTcpSocket::readyRead, this, [=]() {
        // 一次性读取数据
        QByteArray data = m_tcp->readAll();
        if (data.isEmpty()) {
            // ui->record->append("接收到空数据包");
            return;
        }
        if (!m_p.ParseFromString(data.toStdString())) {
            // ui->record->append("反序列化失败！");
            return;
        }
        switch (m_p.type()) {
            case 1: {
                std::string macAddress = m_p.eth().dst();
                QString qMacAddress = QString::fromStdString(macAddress);
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
                ui->record->append("协议类型: ethernetII");
                ui->record->append("目标mac地址: " + qMacAddress);
                macAddress = m_p.eth().src();
                qMacAddress = QString::fromStdString(macAddress);
                ui->record->append("源mac地址: " + qMacAddress);
                QString time = QString::fromStdString(m_p.time());
                QString srcIp = QString::fromStdString(m_p.ip().source_ip());
                QString DstIp = QString::fromStdString(m_p.ip().target_ip());
                QString protocol = "ethernetII";
                QString caplen = QString::number(m_p.caplen());
                append_packet(m_p.type(), time, srcIp, DstIp, protocol, caplen,
                              "");
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
                ui->record->append("\r\n");

            } break;
            case 2: {
                QString time = QString::fromStdString(m_p.time());
                QString srcIp = QString::fromStdString(m_p.arp().source_ip());
                QString DstIp = QString::fromStdString(m_p.arp().target_ip());
                QString protocol = "ARP";
                QString caplen = QString::number(m_p.caplen());
                QString info;
                if (m_p.arp().op_type() == 1)
                    info = "ARP请求";
                else
                    info = "ARP响应";
                append_packet(m_p.type(), time, srcIp, DstIp, protocol, caplen,
                              info);
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
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
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
                ui->record->append("\r\n");
            } break;
            case 3: {
                QString time = QString::fromStdString(m_p.time());
                QString srcIp = QString::fromStdString(m_p.ip().source_ip());
                QString DstIp = QString::fromStdString(m_p.ip().target_ip());
                QString protocol = "IPv4";
                QString caplen = QString::number(m_p.caplen());
                QString info = "ttl=" + QString::number(m_p.ip().ttl()) +
                               " flags=" + QString::number(m_p.ip().flags());
                append_packet(m_p.type(), time, srcIp, DstIp, protocol, caplen,
                              info);
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
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
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
                ui->record->append("\r\n");
            } break;
            case 4: {
                QString time = QString::fromStdString(m_p.time());
                QString srcIp = QString::fromStdString(m_p.ip().source_ip());
                QString DstIp = QString::fromStdString(m_p.ip().target_ip());
                QString protocol = "TCP";
                QString caplen = QString::number(m_p.caplen());
                QString info = QString::number(m_p.tcp().source_port()) +
                               " -> " +
                               QString::number(m_p.tcp().target_port());
                if (m_p.tcp().syn() && m_p.tcp().ack()) {
                    info += " [SYN, ACK]";
                } else if (m_p.tcp().syn()) {
                    info += " [SYN]";
                } else if (m_p.tcp().ack()) {
                    info += " [ACK]";
                }
                info += " Seq=";
                info += QString::number(m_p.tcp().seq_num());
                info += " ACK=";
                info += QString::number(m_p.tcp().ack_num());
                info += " window=";
                info += QString::number(m_p.tcp().window());
                append_packet(m_p.type(), time, srcIp, DstIp, protocol, caplen,
                              info);
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
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
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
                ui->record->append("\r\n");
            } break;
            case 5: {
                QString time = QString::fromStdString(m_p.time());
                QString srcIp = QString::fromStdString(m_p.ip().source_ip());
                QString DstIp = QString::fromStdString(m_p.ip().target_ip());
                QString protocol = "UDP";
                QString caplen = QString::number(m_p.caplen());
                QString info = QString::number(m_p.udp().source_port()) +
                               " -> " +
                               QString::number(m_p.udp().target_port());
                append_packet(m_p.type(), time, srcIp, DstIp, protocol, caplen,
                              info);
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
                ui->record->append("协议类型: udp");
                ui->record->append("checksum: " +
                                   QString::number(m_p.udp().check_sum()));
                ui->record->append("total size: " +
                                   QString::number(m_p.udp().total_size()));
                ui->record->append("source port: " +
                                   QString::number(m_p.udp().source_port()));
                ui->record->append("target_port: " +
                                   QString::number(m_p.udp().target_port()));
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
                ui->record->append("\r\n");
            } break;
            case 7: {
                QString time = QString::fromStdString(m_p.time());
                QString srcIp = QString::fromStdString(m_p.ip().source_ip());
                QString DstIp = QString::fromStdString(m_p.ip().target_ip());
                QString protocol = "HTTP";
                QString caplen = QString::number(m_p.caplen());
                QString info;
                info += QString::fromStdString(m_p.http_request().method());
                info += QString::fromStdString(m_p.http_request().path());
                info +=
                    QString::fromStdString(m_p.http_request().http_version());
                append_packet(m_p.type(), time, srcIp, DstIp, protocol, caplen,
                              info);
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
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
                ui->record->append(
                    "------------------------------------------------------"
                    "---------------------");
                ui->record->append("\r\n");
            } break;
            case 8: {
                QString time = QString::fromStdString(m_p.time());
                QString srcIp = QString::fromStdString(m_p.ip().source_ip());
                QString DstIp = QString::fromStdString(m_p.ip().target_ip());
                QString protocol = "HTTP";
                QString caplen = QString::number(m_p.caplen());
                QString info;
                info +=
                    QString::fromStdString(m_p.http_response().http_version());
                info +=
                    QString::fromStdString(m_p.http_response().status_code());
                info += QString::fromStdString(m_p.http_response().phrase());
                append_packet(m_p.type() - 1, time, srcIp, DstIp, protocol,
                              caplen, info);
                ui->record->append(
                    "----------------------------------------------------------"
                    "-----------------");
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
                    ui->record->append(QString::fromStdString(pair.first) +
                                       ": " +
                                       QString::fromStdString(pair.second));
                }
                ui->record->append(
                    "------------------------------------------------------"
                    "---------------------");
                ui->record->append("\r\n");
            } break;
            default:
                break;
        }
    });

    // 服务端主动断开连接
    connect(m_tcp, &QTcpSocket::disconnected, this, [=]() {
        m_tcp->close();
        // m_tcp->deleteLater(); // delete m_tcp
        m_status->setPixmap(QPixmap(":/false.png").scaled(20, 20));
        qDebug() << "服务端已经和客户端断开了连接....";
        ui->connect->setEnabled(true);
        ui->disconnect->setEnabled(false);
    });

    // 发起连接
    connect(m_tcp, &QTcpSocket::connected, this, [=]() {
        m_status->setPixmap(QPixmap(":/success.png").scaled(20, 20));
        qDebug() << "已经成功连接到服务器....";
        ui->connect->setEnabled(false);
        ui->disconnect->setEnabled(true);
    });

    // 设置表头列数
    ui->tableWidget->setColumnCount(6);
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(
    //        QHeaderView::Stretch);
    //    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
    //        QHeaderView::ResizeToContents);
    // 设置表头各区段大小
    // ui->tableWidget->verticalHeader()->setDefaultSectionSize(30);
    // 设置行表头标题
    QStringList title = {"Time",     "Source", "Destination",
                         "Protocol", "Length", "Info"};
    ui->tableWidget->setHorizontalHeaderLabels(title);

    // 不显示网格线
    ui->tableWidget->setShowGrid(false);
    //单击选择一行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 单元格不可被编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 获取表头视图
    QHeaderView* headerView = ui->tableWidget->horizontalHeader();

    // 设置表头的默认文本对齐方式
    headerView->setDefaultAlignment(Qt::AlignLeft);

    // 添加第一行数据
    int count = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(count + 1);
    QTableWidgetItem* timeItem = new QTableWidgetItem("2024-05-15");
    QTableWidgetItem* srcItem = new QTableWidgetItem("127.0.0.1");
    QTableWidgetItem* dstItem = new QTableWidgetItem("192.168.19.221");
    QTableWidgetItem* typeItem = new QTableWidgetItem("Ethenret");
    QTableWidgetItem* lenItem = new QTableWidgetItem("68");
    QTableWidgetItem* infoItem = new QTableWidgetItem("Infomation");

    ui->tableWidget->setItem(count, 0, timeItem);
    ui->tableWidget->setItem(count, 1, srcItem);
    ui->tableWidget->setItem(count, 2, dstItem);
    ui->tableWidget->setItem(count, 3, typeItem);
    ui->tableWidget->setItem(count, 4, lenItem);
    ui->tableWidget->setItem(count, 5, infoItem);

    for (int i = 0; i < 6; i++) {
        QTableWidgetItem* item = ui->tableWidget->item(count, i);
        if (item) {
            item->setBackground(QColor(255, 165, 0));
        }
    }
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 100);
    ui->tableWidget->setColumnWidth(4, 50);
    ui->tableWidget->setColumnWidth(5, 850);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::append_packet(uint32_t type, QString time, QString source,
                               QString dest, QString prototol, QString len,
                               QString info) {
    int count = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(count + 1);
    QTableWidgetItem* timeItem = new QTableWidgetItem(time);
    QTableWidgetItem* srcItem = new QTableWidgetItem(source);
    QTableWidgetItem* dstItem = new QTableWidgetItem(dest);
    QTableWidgetItem* typeItem = new QTableWidgetItem(prototol);
    QTableWidgetItem* lenItem = new QTableWidgetItem(len);
    QTableWidgetItem* infoItem = new QTableWidgetItem(info);

    ui->tableWidget->setItem(count, 0, timeItem);
    ui->tableWidget->setItem(count, 1, srcItem);
    ui->tableWidget->setItem(count, 2, dstItem);
    ui->tableWidget->setItem(count, 3, typeItem);
    ui->tableWidget->setItem(count, 4, lenItem);
    ui->tableWidget->setItem(count, 5, infoItem);
    switch (type) {
        case 1: {
            for (int i = 0; i < 6; i++) {
                QTableWidgetItem* item = ui->tableWidget->item(count, i);
                if (item) {
                    item->setBackground(QColor(255, 235, 132));
                }
            }
        } break;
        case 2: {
            for (int i = 0; i < 6; i++) {
                QTableWidgetItem* item = ui->tableWidget->item(count, i);
                if (item) {
                    item->setBackground(QColor(135, 206, 250));
                }
            }
        } break;
        case 3: {
            for (int i = 0; i < 6; i++) {
                QTableWidgetItem* item = ui->tableWidget->item(count, i);
                if (item) {
                    item->setBackground(QColor(70, 130, 180));
                }
            }
        } break;
        case 4: {
            for (int i = 0; i < 6; i++) {
                QTableWidgetItem* item = ui->tableWidget->item(count, i);
                if (item) {
                    item->setBackground(QColor(255, 140, 0));
                }
            }
        } break;
        case 5: {
            for (int i = 0; i < 6; i++) {
                QTableWidgetItem* item = ui->tableWidget->item(count, i);
                if (item) {
                    item->setBackground(QColor(0, 155, 125));
                }
            }
        } break;
        case 6: {
            for (int i = 0; i < 6; i++) {
                QTableWidgetItem* item = ui->tableWidget->item(count, i);
                if (item) {
                    item->setBackground(QColor(171, 130, 255));
                }
            }
        } break;
        case 7: {
            for (int i = 0; i < 6; i++) {
                QTableWidgetItem* item = ui->tableWidget->item(count, i);
                if (item) {
                    item->setBackground(QColor(255, 102, 51));
                }
            }
        } break;
        default:
            break;
    }
}

void MainWindow::on_connect_clicked() {
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    m_tcp->connectToHost(QHostAddress(ip), port);
    QColor color;
    uint32_t type = 0;
    if (type == 0)  //以太网
        color = QColor(223, 520, 216);
    //    if (type == 1)  // arp
    //        color
}

// 点击断开连接按钮
void MainWindow::on_disconnect_clicked() {
    m_tcp->close();
    //    ui->connect->setDisabled(false);
    ui->connect->setEnabled(true);
    ui->disconnect->setEnabled(false);
}
