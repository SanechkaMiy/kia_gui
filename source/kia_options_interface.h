#ifndef KIA_OPTIONS_INTERFACE_H
#define KIA_OPTIONS_INTERFACE_H

#include <QWidget>
#include "Kia_main_struct.h"
#include "client.h"
#include <QCheckBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidgetItem>
namespace Ui {
class Kia_options_interface;
}

class Kia_options_interface : public QWidget
{
    Q_OBJECT

public:
    explicit Kia_options_interface(std::shared_ptr<Kia_settings> kia_settings,
                                   std::shared_ptr<Client> client, QWidget *parent = nullptr);
    ~Kia_options_interface();
    void create_window_state_settings(QStringList name_tables, QVector<QStringList> rows_from_table);
    void create_actions_menu_settings(std::vector<std::pair<QString, QList<QAction *> > > actions);
signals:
    void send_state_and_num_row(qint16, qint16, bool);
    void send_color_and_num_row(qint16, qint16, bool);
    void send_num_actions(qint16, qint16, bool);
private slots:
    void set_check_box_for_table_state(qint16 num_table, QStringList active_rows);
    void set_check_box_for_table_state_color(qint16 num_table, QStringList active_rows);
    void set_list_for_menu_actions(qint16 num_menu, QStringList list_actions);
private:
    Ui::Kia_options_interface *ui;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    QTabWidget* m_actions_settings;
    std::vector<std::vector<QCheckBox*>> m_cb_for_data;
    std::vector<std::vector<QCheckBox*>> m_cb_for_color;
    std::vector<QTableWidget*> m_table;
    std::vector<QStringList> m_status;
    std::vector<QStringList> m_color;
    std::vector<QStringList> m_menu_actions;
    std::vector<QListWidget*> m_lw_for_actions;
    std::vector<std::vector<QCheckBox*>> m_cb_for_actions;
};

#endif // KIA_OPTIONS_INTERFACE_H
