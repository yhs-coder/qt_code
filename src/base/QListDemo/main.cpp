#include <QCoreApplication>
#include <QList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> list;
    list << "jerry" << "alex" << "lucy" << "小明";
    for (auto& it : list) {
        qDebug() << it;
    }

    list.push_front("tom");
    list.push_back("jack");

    int len = list.length();

    bool isExist = list.contains("tom");
    qDebug() << isExist;

    // 获得每个元素的值
    // 1. []
    // 2. at(), 会检测是否越界
    qDebug() << list[0];
    qDebug() << list.at(1);


    return a.exec();
}
