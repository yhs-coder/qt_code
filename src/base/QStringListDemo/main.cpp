/*

QString 与 QStringList

std::string 与 wstring <----> QString
*/

#include <QCoreApplication>
#include <string>
#include <iostream>
#include <QDebug>

// QstringList基本用法
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList strList;
    strList << "特斯拉" << "小鹏" << "蔚来";

    auto size = strList.size();
    std::cout << size << std::endl;

    // for (auto& item : strList) {
    //     qDebug() << item;
    // }

    // 追加字符串
    strList.append("小米su7");
    strList.prepend("长城");

    // for (auto& item : strList) {
    //     qDebug() << item;
    // }

    // 插入
    strList.insert(0, "问界");
    for (auto& item : strList) {
        qDebug() << item;
    }
    qDebug() << "-----------";

    // 删除
    strList.removeAt(1);    // 指定位置删除
    strList.removeLast();   // 尾删
    strList.removeFirst();  // 头删
    for (auto& item : strList) {
        qDebug() << item;
    }

    // 替换某个位置的值
    strList.replace(1, "宝马");
    size = strList.size();
    std::cout << size << std::endl;
    for (auto& item : strList) {
        qDebug() << item;
    }

    // 将QStringList 中的字符串 合并为一个字符串，以逗号分割
    QString str = strList.join(",");
    qDebug() << str;

    // 以某个符号拆分QString,存入QStringList
    QString str2 = "张三,李四,王五";
    QStringList strList2 = str2.split(",");
    for (auto& item : strList2) {
        qDebug() << item;
    }


    return a.exec();
}

#if 0
// Qstring 与 std::string / std::wstring的转换
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string str = "你好";
    // QString::fromStdString(): 从std::string 转为 QString
    QString qstr = QString::fromStdString(str);
    qDebug() << qstr;

    // 如果编码器使用的是msvc,并且系统编码是gbk编码
    // 需要使用QString::fromLocal8Bit(), 将gbk编码转为utf-8
    // 也就是string转为QString
    // 避免输出显示乱码
    // QString qstr2 = QString::fromLocal8Bit(str.data());
    // qDebug() << qstr2;

    // 同理，QString 转为 std::string
    // 使用toLocal8Bit()
    // qstr2.toLocal8Bit();

    std::string str2 = "China";
    QString qstr3 = QString::fromStdString(str2);
    qDebug() << qstr3;


    // QStrin 转为 wstring
    QString qstr4 = "hello qt";
    std::wstring wstr1 = qstr4.toStdWString();


    return a.exec();
}
#endif
