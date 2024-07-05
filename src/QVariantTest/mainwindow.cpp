#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVariant>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 整型数
    int value = dataPlus(10, 20).toInt();
    // 字符串
    QString str = dataPlus("hello ", "world!").toString();
    qDebug() << "int value:" <<value;
    qDebug() << "QString string :" <<str;

    /**
        QVariant对象存储自定义类型的数据
    **/
    Person p {100, "张三"};

// 对于自定义类型，QVariant对象有两种初始化方式
#if 1
    // 首先使用QVariant()创建一个对象，
    // 然后使用设置函数将自定义类型的数据设置到QVariant对象中
    QVariant v;
    v.setValue(p);
#else
    // 使用静态成员函数fromValue()，功能和setValue()一样,返回QVariant对象
    QVariant v = QVariant::fromValue(p);
#endif
    // 取出v对象的数据
    /**
        如果当前QVariant对象可用转换为对应的模板类型 T, 返回true, 否则返回false
        bool QVariant::canConvert() const;

        将当前QVariant对象转换为实际的 T 类型
        T QVariant::value() const;
    **/
    if (v.canConvert<Person>())
    {
        Person tmp = v.value<Person>();
        qDebug() << "id: " << tmp.id << " , name : " << tmp.name;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVariant MainWindow::dataPlus(QVariant a, QVariant b)
{
    QVariant ret;
    // 判断当前参数的类型是整型还是字符串
    // type()函数和QVarint类型，自qt6.0以后被弃用，应该使用typeId() 或者metaType() 代替.
    //if (a.type() == QVariant::Int && b.type() == QVariant::Int)
    if (a.typeId() == QMetaType::Int && b.typeId() == QMetaType::Int)
    {
        ret = QVariant(a.toInt() + b.toInt());
    }
    //if (a.typeId() == QVariant::QString && b.typeId() == QVariant::String)
    if (a.typeId() == QMetaType::QString && b.typeId() == QMetaType::QString)
    {
        ret.setValue(a.toString() + b.toString());
    }
    return ret;
}



