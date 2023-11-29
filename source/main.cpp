#include <QApplication>
#include <QDebug>
#include <iostream>
#include <string>
#include <vector>
#include <kiacore.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font(":/font/fonts/JetBrainsMono-ExtraLight.ttf", 10);
    QApplication::setFont(font);
    KiaCore core;
    return a.exec();
}
