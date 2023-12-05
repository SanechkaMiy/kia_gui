#ifndef KIAWINDOWISWORK_H
#define KIAWINDOWISWORK_H
#include <QtWidgets/QWidget>
#include "kled.h"
#include <QDialog>
#include <QLayout>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <vector>
#include "client.h"
#include "Kia_main_struct.h"
#include <QHeaderView>
#include <QBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QShortcut>
namespace Ui {
class KiaWindowIsWork;
}

class KiaWindowIsWork : public QDialog
{
    Q_OBJECT

public:
    explicit KiaWindowIsWork(std::shared_ptr<Kia_settings> kia_settings,
                             std::shared_ptr<Client> client, QWidget *parent = nullptr);
    ~KiaWindowIsWork();
    void create_table_status_bokz();
public slots:
    void set_width_for_vertical_header(qint16 width_header, qint16 width_col);
    void create_status_bi();
    void check_connect(qint16 type_kled, qint16 is_con_to_core);
    void set_data_to_table(QStringList data);
    void set_stop_slot();
signals:
    void set_stop(qint16);
    void send_widget(QWidget*);
private:
    QPushButton* m_pb_stop;
    QTableWidget* m_set_table;
    QCheckBox* m_cb_is_otclp;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    Ui::KiaWindowIsWork *ui;
    QLabel* m_label_db;
    QLabel* m_label_console;
    KLed* m_kled_status_db;
    KLed* m_kled_status_connect_to_console;
    std::vector<KLed*> m_kled_statuc_connect;
    qint16 m_is_otclp = 0;
    std::vector<QLineEdit* > m_line_edit_bshv;
    std::vector<QLineEdit* > m_line_edit_st1;
    std::vector<QLineEdit* > m_line_edit_st2;
    bool m_is_set_data_bshv = true;
};

#endif // KIAWINDOWISWORK_H
