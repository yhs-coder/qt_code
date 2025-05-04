#include "widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <memory>

#include "./ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lbImage->clear();
}

Widget::~Widget() { delete ui; }

void Widget::open1()
{
    QString fileName = QFileDialog::getOpenFileName(this, "请选择图片", "D:/", "图片(*.png)");

    if (fileName.isEmpty()) {
        return;
    }
    ui->lineEditPath->setText(fileName);
    ui->lbImage->setPixmap(QPixmap(fileName));
}

void Widget::open2()
{
    QString config_path = qApp->applicationDirPath() + "/config/setting.ini";
    qDebug() << config_path;

    // QSettings 读取 INI 文件配置
    std::unique_ptr<QSettings> pIniSet(new QSettings(config_path, QSettings::IniFormat));
    // QSettings* pIniSet  = new QSettings(config_path, QSettings::IniFormat);
    QString lastPath = pIniSet->value("/LastPath/path").toString();

    if (lastPath.isEmpty()) {
        // 如果路径为空，设置默认路径
        lastPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    }

    QString fileName = QFileDialog::getOpenFileName(this, "请选择图片", lastPath, "图片(*.png)");

    if (fileName.isEmpty()) {
        return;
    }

    int     end   = fileName.lastIndexOf("/");
    QString _path = fileName.left(end);
    // ui->lineEditPath->setText(_path);
    qDebug() << _path;

    std::unique_ptr<QPixmap> pix(new QPixmap(fileName));
    pix->scaled(ui->lbImage->size(), Qt::KeepAspectRatio);
    ui->lbImage->setScaledContents(true);

    ui->lineEditPath->setText(fileName);
    ui->lbImage->setPixmap(*pix);

    // 当前选择的路径写入ini文件
    pIniSet->setValue("/LastPath/path", _path);
    pIniSet->sync();  // 确保立即生效
    // delete pIniSet;
    // pIniSet = nullptr;
}

void Widget::on_btnOpen_clicked()
{
    // open1();
    open2();
}
