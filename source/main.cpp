#include <QApplication>
#include <QDebug>
#include <iostream>
#include <string>
#include <vector>
#include <kiacore.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KiaCore core;
    return a.exec();
}
