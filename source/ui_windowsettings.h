/********************************************************************************
** Form generated from reading UI file 'windowsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWSETTINGS_H
#define UI_WINDOWSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowSettings
{
public:
    QTableWidget *tableWidget;
    QProgressBar *progressBar_bokz1;
    QProgressBar *progressBar_bokz2;
    QProgressBar *progressBar_bokz3;
    QProgressBar *progressBar_bokz4;
    QCheckBox *checkBox_bokz1;
    QCheckBox *checkBox_bokz2;
    QCheckBox *checkBox_bokz3;
    QCheckBox *checkBox_bokz4;
    QComboBox *comboBox_1;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;

    void setupUi(QWidget *WindowSettings)
    {
        if (WindowSettings->objectName().isEmpty())
            WindowSettings->setObjectName(QString::fromUtf8("WindowSettings"));
        WindowSettings->resize(565, 373);
        tableWidget = new QTableWidget(WindowSettings);
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
        if (tableWidget->rowCount() < 23)
            tableWidget->setRowCount(23);
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
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(16, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(17, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(18, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(19, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(20, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(21, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(22, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem27);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 561, 371));
        progressBar_bokz1 = new QProgressBar(WindowSettings);
        progressBar_bokz1->setObjectName(QString::fromUtf8("progressBar_bokz1"));
        progressBar_bokz1->setEnabled(false);
        progressBar_bokz1->setGeometry(QRect(130, 50, 118, 23));
        progressBar_bokz1->setValue(0);
        progressBar_bokz2 = new QProgressBar(WindowSettings);
        progressBar_bokz2->setObjectName(QString::fromUtf8("progressBar_bokz2"));
        progressBar_bokz2->setEnabled(false);
        progressBar_bokz2->setGeometry(QRect(250, 50, 118, 23));
        progressBar_bokz2->setValue(0);
        progressBar_bokz3 = new QProgressBar(WindowSettings);
        progressBar_bokz3->setObjectName(QString::fromUtf8("progressBar_bokz3"));
        progressBar_bokz3->setEnabled(false);
        progressBar_bokz3->setGeometry(QRect(340, 50, 118, 23));
        progressBar_bokz3->setValue(0);
        progressBar_bokz4 = new QProgressBar(WindowSettings);
        progressBar_bokz4->setObjectName(QString::fromUtf8("progressBar_bokz4"));
        progressBar_bokz4->setEnabled(false);
        progressBar_bokz4->setGeometry(QRect(440, 50, 118, 23));
        progressBar_bokz4->setValue(0);
        checkBox_bokz1 = new QCheckBox(WindowSettings);
        checkBox_bokz1->setObjectName(QString::fromUtf8("checkBox_bokz1"));
        checkBox_bokz1->setGeometry(QRect(140, 30, 85, 21));
        checkBox_bokz2 = new QCheckBox(WindowSettings);
        checkBox_bokz2->setObjectName(QString::fromUtf8("checkBox_bokz2"));
        checkBox_bokz2->setGeometry(QRect(250, 30, 85, 21));
        checkBox_bokz3 = new QCheckBox(WindowSettings);
        checkBox_bokz3->setObjectName(QString::fromUtf8("checkBox_bokz3"));
        checkBox_bokz3->setGeometry(QRect(360, 20, 85, 21));
        checkBox_bokz4 = new QCheckBox(WindowSettings);
        checkBox_bokz4->setObjectName(QString::fromUtf8("checkBox_bokz4"));
        checkBox_bokz4->setGeometry(QRect(460, 20, 85, 21));
        comboBox_1 = new QComboBox(WindowSettings);
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->setObjectName(QString::fromUtf8("comboBox_1"));
        comboBox_1->setGeometry(QRect(150, 90, 79, 23));
        comboBox_1->setMaxVisibleItems(10);
        comboBox_1->setInsertPolicy(QComboBox::NoInsert);
        comboBox_2 = new QComboBox(WindowSettings);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(250, 90, 79, 23));
        comboBox_2->setMaxVisibleItems(10);
        comboBox_2->setInsertPolicy(QComboBox::NoInsert);
        comboBox_3 = new QComboBox(WindowSettings);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(350, 80, 79, 23));
        comboBox_3->setMaxVisibleItems(10);
        comboBox_3->setInsertPolicy(QComboBox::NoInsert);
        comboBox_4 = new QComboBox(WindowSettings);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(450, 80, 79, 23));
        comboBox_4->setMaxVisibleItems(10);
        comboBox_4->setInsertPolicy(QComboBox::NoInsert);

        retranslateUi(WindowSettings);

        QMetaObject::connectSlotsByName(WindowSettings);
    } // setupUi

    void retranslateUi(QWidget *WindowSettings)
    {
        WindowSettings->setWindowTitle(QCoreApplication::translate("WindowSettings", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("WindowSettings", "\320\221\320\236\320\232\320\227 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("WindowSettings", "\320\221\320\236\320\232\320\227 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("WindowSettings", "\320\221\320\236\320\232\320\227 3", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("WindowSettings", "\320\221\320\236\320\232\320\227 4", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("WindowSettings", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("WindowSettings", "\320\237\321\200\320\276\320\263\321\200\320\265\321\201\321\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("WindowSettings", "\320\220\320\264\321\200\320\265\321\201 \320\234\320\237\320\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("WindowSettings", "\320\223\321\200\321\203\320\277\320\277\320\260 \320\242\320\224", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("WindowSettings", "\320\234\320\237\320\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("WindowSettings", "\320\221\320\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("WindowSettings", "\320\222\321\200\320\265\320\274\321\217 \320\275\320\260\321\200\320\260\320\261\320\276\321\202\320\272\320\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("WindowSettings", "\320\222\321\200\320\265\320\274\321\217 \320\277\321\200\320\270\320\262\321\217\320\267\320\272\320\270, \321\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("WindowSettings", "\320\222\321\200\320\265\320\274\321\217 \320\277\321\200\320\270\320\262\321\217\320\267\320\272\320\270, \320\274\321\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("WindowSettings", "Qa0", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("WindowSettings", "Qa1", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("WindowSettings", "Qa2", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("WindowSettings", "Qa3", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("WindowSettings", "Vx[\320\272\320\274/\321\201]", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("WindowSettings", "Vy[\320\272\320\274/\321\201]", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("WindowSettings", "Vz[\320\272\320\274/\321\201]", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->verticalHeaderItem(16);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("WindowSettings", "Wx[\321\200\320\260\320\264/\321\201]", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->verticalHeaderItem(17);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("WindowSettings", "Wy[\320\240\320\260\320\264/\321\201]", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->verticalHeaderItem(18);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("WindowSettings", "Wz[\320\240\320\260\320\264/\321\201]", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->verticalHeaderItem(19);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("WindowSettings", "Fx[\320\240\320\260\320\264/\321\201^2]", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->verticalHeaderItem(20);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("WindowSettings", "Fy[\320\240\320\260\320\264/\321\201^2]", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->verticalHeaderItem(21);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("WindowSettings", "Fz[\320\240\320\260\320\264/\321\201^2]", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->verticalHeaderItem(22);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("WindowSettings", "\320\221\320\250\320\222", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        checkBox_bokz1->setText(QCoreApplication::translate("WindowSettings", "\320\235\320\265\321\202", nullptr));
        checkBox_bokz2->setText(QCoreApplication::translate("WindowSettings", "\320\235\320\265\321\202", nullptr));
        checkBox_bokz3->setText(QCoreApplication::translate("WindowSettings", "\320\235\320\265\321\202", nullptr));
        checkBox_bokz4->setText(QCoreApplication::translate("WindowSettings", "\320\235\320\265\321\202", nullptr));
        comboBox_1->setItemText(0, QCoreApplication::translate("WindowSettings", "0", nullptr));
        comboBox_1->setItemText(1, QCoreApplication::translate("WindowSettings", "1", nullptr));
        comboBox_1->setItemText(2, QCoreApplication::translate("WindowSettings", "2", nullptr));
        comboBox_1->setItemText(3, QCoreApplication::translate("WindowSettings", "3", nullptr));
        comboBox_1->setItemText(4, QCoreApplication::translate("WindowSettings", "4", nullptr));
        comboBox_1->setItemText(5, QCoreApplication::translate("WindowSettings", "5", nullptr));
        comboBox_1->setItemText(6, QCoreApplication::translate("WindowSettings", "6", nullptr));
        comboBox_1->setItemText(7, QCoreApplication::translate("WindowSettings", "7", nullptr));
        comboBox_1->setItemText(8, QCoreApplication::translate("WindowSettings", "8", nullptr));
        comboBox_1->setItemText(9, QCoreApplication::translate("WindowSettings", "9", nullptr));
        comboBox_1->setItemText(10, QCoreApplication::translate("WindowSettings", "10", nullptr));
        comboBox_1->setItemText(11, QCoreApplication::translate("WindowSettings", "11", nullptr));
        comboBox_1->setItemText(12, QCoreApplication::translate("WindowSettings", "12", nullptr));
        comboBox_1->setItemText(13, QCoreApplication::translate("WindowSettings", "13", nullptr));
        comboBox_1->setItemText(14, QCoreApplication::translate("WindowSettings", "14", nullptr));
        comboBox_1->setItemText(15, QCoreApplication::translate("WindowSettings", "15", nullptr));
        comboBox_1->setItemText(16, QCoreApplication::translate("WindowSettings", "16", nullptr));
        comboBox_1->setItemText(17, QCoreApplication::translate("WindowSettings", "17", nullptr));
        comboBox_1->setItemText(18, QCoreApplication::translate("WindowSettings", "18", nullptr));
        comboBox_1->setItemText(19, QCoreApplication::translate("WindowSettings", "19", nullptr));
        comboBox_1->setItemText(20, QCoreApplication::translate("WindowSettings", "20", nullptr));
        comboBox_1->setItemText(21, QCoreApplication::translate("WindowSettings", "21", nullptr));
        comboBox_1->setItemText(22, QCoreApplication::translate("WindowSettings", "22", nullptr));
        comboBox_1->setItemText(23, QCoreApplication::translate("WindowSettings", "23", nullptr));
        comboBox_1->setItemText(24, QCoreApplication::translate("WindowSettings", "24", nullptr));
        comboBox_1->setItemText(25, QCoreApplication::translate("WindowSettings", "25", nullptr));
        comboBox_1->setItemText(26, QCoreApplication::translate("WindowSettings", "26", nullptr));
        comboBox_1->setItemText(27, QCoreApplication::translate("WindowSettings", "27", nullptr));
        comboBox_1->setItemText(28, QCoreApplication::translate("WindowSettings", "28", nullptr));
        comboBox_1->setItemText(29, QCoreApplication::translate("WindowSettings", "29", nullptr));
        comboBox_1->setItemText(30, QCoreApplication::translate("WindowSettings", "30", nullptr));
        comboBox_1->setItemText(31, QCoreApplication::translate("WindowSettings", "31", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("WindowSettings", "0", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("WindowSettings", "1", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("WindowSettings", "2", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("WindowSettings", "3", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("WindowSettings", "4", nullptr));
        comboBox_2->setItemText(5, QCoreApplication::translate("WindowSettings", "5", nullptr));
        comboBox_2->setItemText(6, QCoreApplication::translate("WindowSettings", "6", nullptr));
        comboBox_2->setItemText(7, QCoreApplication::translate("WindowSettings", "7", nullptr));
        comboBox_2->setItemText(8, QCoreApplication::translate("WindowSettings", "8", nullptr));
        comboBox_2->setItemText(9, QCoreApplication::translate("WindowSettings", "9", nullptr));
        comboBox_2->setItemText(10, QCoreApplication::translate("WindowSettings", "10", nullptr));
        comboBox_2->setItemText(11, QCoreApplication::translate("WindowSettings", "11", nullptr));
        comboBox_2->setItemText(12, QCoreApplication::translate("WindowSettings", "12", nullptr));
        comboBox_2->setItemText(13, QCoreApplication::translate("WindowSettings", "13", nullptr));
        comboBox_2->setItemText(14, QCoreApplication::translate("WindowSettings", "14", nullptr));
        comboBox_2->setItemText(15, QCoreApplication::translate("WindowSettings", "15", nullptr));
        comboBox_2->setItemText(16, QCoreApplication::translate("WindowSettings", "16", nullptr));
        comboBox_2->setItemText(17, QCoreApplication::translate("WindowSettings", "17", nullptr));
        comboBox_2->setItemText(18, QCoreApplication::translate("WindowSettings", "18", nullptr));
        comboBox_2->setItemText(19, QCoreApplication::translate("WindowSettings", "19", nullptr));
        comboBox_2->setItemText(20, QCoreApplication::translate("WindowSettings", "20", nullptr));
        comboBox_2->setItemText(21, QCoreApplication::translate("WindowSettings", "21", nullptr));
        comboBox_2->setItemText(22, QCoreApplication::translate("WindowSettings", "22", nullptr));
        comboBox_2->setItemText(23, QCoreApplication::translate("WindowSettings", "23", nullptr));
        comboBox_2->setItemText(24, QCoreApplication::translate("WindowSettings", "24", nullptr));
        comboBox_2->setItemText(25, QCoreApplication::translate("WindowSettings", "25", nullptr));
        comboBox_2->setItemText(26, QCoreApplication::translate("WindowSettings", "26", nullptr));
        comboBox_2->setItemText(27, QCoreApplication::translate("WindowSettings", "27", nullptr));
        comboBox_2->setItemText(28, QCoreApplication::translate("WindowSettings", "28", nullptr));
        comboBox_2->setItemText(29, QCoreApplication::translate("WindowSettings", "29", nullptr));
        comboBox_2->setItemText(30, QCoreApplication::translate("WindowSettings", "30", nullptr));
        comboBox_2->setItemText(31, QCoreApplication::translate("WindowSettings", "31", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("WindowSettings", "0", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("WindowSettings", "1", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("WindowSettings", "2", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("WindowSettings", "3", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("WindowSettings", "4", nullptr));
        comboBox_3->setItemText(5, QCoreApplication::translate("WindowSettings", "5", nullptr));
        comboBox_3->setItemText(6, QCoreApplication::translate("WindowSettings", "6", nullptr));
        comboBox_3->setItemText(7, QCoreApplication::translate("WindowSettings", "7", nullptr));
        comboBox_3->setItemText(8, QCoreApplication::translate("WindowSettings", "8", nullptr));
        comboBox_3->setItemText(9, QCoreApplication::translate("WindowSettings", "9", nullptr));
        comboBox_3->setItemText(10, QCoreApplication::translate("WindowSettings", "10", nullptr));
        comboBox_3->setItemText(11, QCoreApplication::translate("WindowSettings", "11", nullptr));
        comboBox_3->setItemText(12, QCoreApplication::translate("WindowSettings", "12", nullptr));
        comboBox_3->setItemText(13, QCoreApplication::translate("WindowSettings", "13", nullptr));
        comboBox_3->setItemText(14, QCoreApplication::translate("WindowSettings", "14", nullptr));
        comboBox_3->setItemText(15, QCoreApplication::translate("WindowSettings", "15", nullptr));
        comboBox_3->setItemText(16, QCoreApplication::translate("WindowSettings", "16", nullptr));
        comboBox_3->setItemText(17, QCoreApplication::translate("WindowSettings", "17", nullptr));
        comboBox_3->setItemText(18, QCoreApplication::translate("WindowSettings", "18", nullptr));
        comboBox_3->setItemText(19, QCoreApplication::translate("WindowSettings", "19", nullptr));
        comboBox_3->setItemText(20, QCoreApplication::translate("WindowSettings", "20", nullptr));
        comboBox_3->setItemText(21, QCoreApplication::translate("WindowSettings", "21", nullptr));
        comboBox_3->setItemText(22, QCoreApplication::translate("WindowSettings", "22", nullptr));
        comboBox_3->setItemText(23, QCoreApplication::translate("WindowSettings", "23", nullptr));
        comboBox_3->setItemText(24, QCoreApplication::translate("WindowSettings", "24", nullptr));
        comboBox_3->setItemText(25, QCoreApplication::translate("WindowSettings", "25", nullptr));
        comboBox_3->setItemText(26, QCoreApplication::translate("WindowSettings", "26", nullptr));
        comboBox_3->setItemText(27, QCoreApplication::translate("WindowSettings", "27", nullptr));
        comboBox_3->setItemText(28, QCoreApplication::translate("WindowSettings", "28", nullptr));
        comboBox_3->setItemText(29, QCoreApplication::translate("WindowSettings", "29", nullptr));
        comboBox_3->setItemText(30, QCoreApplication::translate("WindowSettings", "30", nullptr));
        comboBox_3->setItemText(31, QCoreApplication::translate("WindowSettings", "31", nullptr));

        comboBox_4->setItemText(0, QCoreApplication::translate("WindowSettings", "0", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("WindowSettings", "1", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("WindowSettings", "2", nullptr));
        comboBox_4->setItemText(3, QCoreApplication::translate("WindowSettings", "3", nullptr));
        comboBox_4->setItemText(4, QCoreApplication::translate("WindowSettings", "4", nullptr));
        comboBox_4->setItemText(5, QCoreApplication::translate("WindowSettings", "5", nullptr));
        comboBox_4->setItemText(6, QCoreApplication::translate("WindowSettings", "6", nullptr));
        comboBox_4->setItemText(7, QCoreApplication::translate("WindowSettings", "7", nullptr));
        comboBox_4->setItemText(8, QCoreApplication::translate("WindowSettings", "8", nullptr));
        comboBox_4->setItemText(9, QCoreApplication::translate("WindowSettings", "9", nullptr));
        comboBox_4->setItemText(10, QCoreApplication::translate("WindowSettings", "10", nullptr));
        comboBox_4->setItemText(11, QCoreApplication::translate("WindowSettings", "11", nullptr));
        comboBox_4->setItemText(12, QCoreApplication::translate("WindowSettings", "12", nullptr));
        comboBox_4->setItemText(13, QCoreApplication::translate("WindowSettings", "13", nullptr));
        comboBox_4->setItemText(14, QCoreApplication::translate("WindowSettings", "14", nullptr));
        comboBox_4->setItemText(15, QCoreApplication::translate("WindowSettings", "15", nullptr));
        comboBox_4->setItemText(16, QCoreApplication::translate("WindowSettings", "16", nullptr));
        comboBox_4->setItemText(17, QCoreApplication::translate("WindowSettings", "17", nullptr));
        comboBox_4->setItemText(18, QCoreApplication::translate("WindowSettings", "18", nullptr));
        comboBox_4->setItemText(19, QCoreApplication::translate("WindowSettings", "19", nullptr));
        comboBox_4->setItemText(20, QCoreApplication::translate("WindowSettings", "20", nullptr));
        comboBox_4->setItemText(21, QCoreApplication::translate("WindowSettings", "21", nullptr));
        comboBox_4->setItemText(22, QCoreApplication::translate("WindowSettings", "22", nullptr));
        comboBox_4->setItemText(23, QCoreApplication::translate("WindowSettings", "23", nullptr));
        comboBox_4->setItemText(24, QCoreApplication::translate("WindowSettings", "24", nullptr));
        comboBox_4->setItemText(25, QCoreApplication::translate("WindowSettings", "25", nullptr));
        comboBox_4->setItemText(26, QCoreApplication::translate("WindowSettings", "26", nullptr));
        comboBox_4->setItemText(27, QCoreApplication::translate("WindowSettings", "27", nullptr));
        comboBox_4->setItemText(28, QCoreApplication::translate("WindowSettings", "28", nullptr));
        comboBox_4->setItemText(29, QCoreApplication::translate("WindowSettings", "29", nullptr));
        comboBox_4->setItemText(30, QCoreApplication::translate("WindowSettings", "30", nullptr));
        comboBox_4->setItemText(31, QCoreApplication::translate("WindowSettings", "31", nullptr));

    } // retranslateUi

};

namespace Ui {
    class WindowSettings: public Ui_WindowSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWSETTINGS_H
