#include <QCoreApplication>
#include <QVector>
#include <QDebug>

// QVector基本用法
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 基本用法和std::vector类似

    QVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    // 遍历
    for (auto& num : v) {
        qDebug() << num;
    }

    // 元素个数
    int len = v.size();
    int len2 = v.length();
    int len3 = v.count();
    qDebug() << "size = " << len;

    // 弹出元素
    // 弹出头元素
    v.pop_front();
    len = v.size();
    qDebug() << "after pop_front, size = " << len;

    // 删除
    v.remove(0);
    len = v.size();
    qDebug() << "after remove, size = " << len;
    for (auto& num : v) {
        qDebug() << num;
    }

    // 插入数据
    v.insert(0, 100);
    v.insert(1, 111);
    for (auto& num : v) {
        qDebug() << num;
    }

    // 追加
    v.append(500);
    v.prepend(600);
    qDebug() << "------------" ;
    for (auto& num : v) {
        qDebug() << num;
    }

    v.clear();
    qDebug() << v.isEmpty();

    return a.exec();
}
