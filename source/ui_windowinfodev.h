/********************************************************************************
** Form generated from reading UI file 'windowinfodev.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWINFODEV_H
#define UI_WINDOWINFODEV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowInfoDev
{
public:
    QTextBrowser *textBrowser;

    void setupUi(QWidget *WindowInfoDev)
    {
        if (WindowInfoDev->objectName().isEmpty())
            WindowInfoDev->setObjectName(QString::fromUtf8("WindowInfoDev"));
        WindowInfoDev->resize(652, 505);
        textBrowser = new QTextBrowser(WindowInfoDev);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(0, 0, 501, 491));

        retranslateUi(WindowInfoDev);

        QMetaObject::connectSlotsByName(WindowInfoDev);
    } // setupUi

    void retranslateUi(QWidget *WindowInfoDev)
    {
        WindowInfoDev->setWindowTitle(QCoreApplication::translate("WindowInfoDev", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowInfoDev: public Ui_WindowInfoDev {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWINFODEV_H
