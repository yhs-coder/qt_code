#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str1 = "123";
    QString str2 = "456";

    // 字符串转为数字
    int  a1 = str1.toInt();
    int a2 = str2.toInt();

    qDebug() << a1 + a2;

    // 数字转QString
    int a3 = 11;
    // 16表示的是进制,不写默认十进制
    QString str3 = QString::number(a3);
    qDebug() << str3;

    // 字符串拼接
    QString str4 = "hello ";
    // utf-8编码，每个中文字符算一个字节
    QString str5 = "Qt中国";
    qDebug() << str4 + str5;

    // append() 字符串后追加字符串
    // prepend() 字符串前追加接字符串
    str4.append(str5);
    qDebug() << str4;
    str4.prepend("OMG!");
    qDebug() << str4;

    // 转换大小写
    // toLower() 字符串转为小写
    // toUpper() 字符串转为大写
    QString str6 = str4.toLower();
    qDebug() << str6;

    QString str7 = str4.toUpper();
    qDebug() << str7;

    // count,size, length : 计算字符串的长度
    auto len1 = str4.size();
    auto len2 = str4.length();
    auto len3 = str5.count();
    qDebug() << len1 << " " << len2 << " " << len3;

    // trimmed() 去掉字符串首尾的空格
    QString str8 = " Are you ok?   ";
    QString str9 = str8.trimmed();
    qDebug() << str8;
    qDebug() << str9;

    // simplified(): 不管有多少空格，处理后每个字符串之间只用一个空格间隔
    QString str10 = "  Are   you   ok  ?   ";
    QString str11 = str10.simplified();
    qDebug() << str11;

    // lastIndexOf(): 查找最后一个分隔符或者最后一个字符串的位置
    QString str12 = "D:/workspace/file/image/hello.png";
    int last = str12.lastIndexOf('/');
    int png = str12.lastIndexOf(".png");
    qDebug() << last << " " << png;

    // isNull(), isEmpty(): 判断字符串是否为空
    // isNull()：判断字符串对象是否初始化（未初始化返回true）
    // isEmpty()：判断字符串内容是否为空（包含\0也视为空）
    // 优先使用isEmpty()
    QString str13;
    QString str14 = "";

    qDebug() << str13.isNull() << " " << str13.isEmpty();
    qDebug() << str14.isNull() << " " << str14.isEmpty();


    // contains(): 判断是否包含某个字符串
    // Qt::CaseSensitive 表示区分大小写
    // Qt::CaseInsensitive 表示不区分大小写
    QString str15 = "hello world!";
    //是否包含 or
    bool isCon = str15.contains("or", Qt::CaseSensitive);
    qDebug() << "or的位置为： "  << isCon;

    // endsWith(): 是否以特定的后缀结尾
    QString name = "test.MP4";
    bool ismp4 = name.endsWith(".mp4", Qt::CaseSensitive);
    qDebug() << "ismp4 = " << ismp4;

    // 判断是否已特定字符串开头
    bool isStart = name.startsWith("TE", Qt::CaseInsensitive);
    qDebug() << "isStart = " << isStart;

    return 0;
}
