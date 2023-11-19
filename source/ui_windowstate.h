/********************************************************************************
** Form generated from reading UI file 'windowstate.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWSTATE_H
#define UI_WINDOWSTATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>
#include "kled.h"

QT_BEGIN_NAMESPACE

class Ui_WindowState
{
public:
    QTableWidget *tableWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTimeEdit *timeEdit;
    KLed *kled_bi;
    KLed *kled_timer;
    QCheckBox *checkBox;
    QPushButton *pushButton;

    void setupUi(QWidget *WindowState)
    {
        if (WindowState->objectName().isEmpty())
            WindowState->setObjectName(QString::fromUtf8("WindowState"));
        WindowState->resize(543, 474);
        tableWidget = new QTableWidget(WindowState);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget->rowCount() < 14)
            tableWidget->setRowCount(14);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem17);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 30, 541, 441));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        horizontalLayoutWidget = new QWidget(WindowState);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 365, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        timeEdit = new QTimeEdit(horizontalLayoutWidget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));

        horizontalLayout->addWidget(timeEdit);

        kled_bi = new KLed(horizontalLayoutWidget);
        kled_bi->setObjectName(QString::fromUtf8("kled_bi"));

        horizontalLayout->addWidget(kled_bi);

        kled_timer = new KLed(horizontalLayoutWidget);
        kled_timer->setObjectName(QString::fromUtf8("kled_timer"));

        horizontalLayout->addWidget(kled_timer);

        checkBox = new QCheckBox(horizontalLayoutWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(WindowState);

        QMetaObject::connectSlotsByName(WindowState);
    } // setupUi

    void retranslateUi(QWidget *WindowState)
    {
        WindowState->setWindowTitle(QCoreApplication::translate("WindowState", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("WindowState", "\320\232\320\260\320\275\320\260\320\273 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("WindowState", "\320\232\320\260\320\275\320\260\320\273 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("WindowState", "\320\232\320\260\320\275\320\260\320\273 3", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("WindowState", "\320\232\320\260\320\275\320\260\320\273 4", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("WindowState", "\320\221\320\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("WindowState", "\320\232\320\241", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("WindowState", "\320\221\320\240\320\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("WindowState", "\320\221\320\242\320\222\320\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("WindowState", "\320\232\320\240\320\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("WindowState", "\320\221\320\240\320\242\320\243\320\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("WindowState", "\320\230\320\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("WindowState", "\320\221\320\242\320\222\320\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("WindowState", "\320\244\320\270\320\264\320\265\321\200 1 \320\277\321\200\320\270\320\261\320\276\321\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("WindowState", "\320\244\320\270\320\264\320\265\321\200 2 \320\277\321\200\320\270\320\261\320\276\321\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("WindowState", "\320\244\320\270\320\264\320\265\321\200 1 \320\270\320\274\320\270\321\202\320\260\321\202\320\276\321\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("WindowState", "\320\244\320\270\320\264\320\265\321\200 2 \320\270\320\274\320\270\321\202\320\260\321\202\320\276\321\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("WindowState", "\320\242\320\2241", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("WindowState", "\320\242\320\2242", nullptr));
        label->setText(QCoreApplication::translate("WindowState", "\320\221\320\250\320\222", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("WindowState", "h:mm:ss", nullptr));
        checkBox->setText(QCoreApplication::translate("WindowState", "\320\236\320\242\320\232\320\233 \320\240", nullptr));
        pushButton->setText(QCoreApplication::translate("WindowState", "\320\241\320\242\320\236\320\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowState: public Ui_WindowState {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWSTATE_H
