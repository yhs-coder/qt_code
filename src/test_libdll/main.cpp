#include <QCoreApplication>
#include <iostream>
#include "test.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "test libdll" << endl;
    Test t;

    return a.exec();
}
