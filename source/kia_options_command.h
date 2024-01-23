#ifndef KIA_OPTIONS_COMMAND_H
#define KIA_OPTIONS_COMMAND_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLineEdit>
#include <QToolBox>
#include <QGridLayout>
#include <iostream>
#include "Kia_main_struct.h"
#include <utility>
#include "client.h"
#include <fstream>
#include <string.h>
namespace Ui {
class Kia_options_command;
}

class Kia_options_command : public QWidget
{
    Q_OBJECT

public:
    explicit Kia_options_command(std::shared_ptr<Kia_settings> kia_settings,
                                 std::shared_ptr<Client> client, QWidget *parent = nullptr);
    ~Kia_options_command();
public slots:
    void set_read_command(qint16 num_bokz, qint16 type_data, qint16 type_command, QStringList data);

private slots:
    void on_set_param_clicked();

    void on_get_param_clicked();

    void on_load_param_clicked();

private:
    Ui::Kia_options_command *ui;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    QTabWidget* m_command_settings;
    std::vector<QTabWidget*> m_tab_for_type_command;
    std::vector<QVBoxLayout*> m_layout_for_place_tab_widget;
    QGridLayout* m_layout_for_all_widget;
    QGridLayout* m_layout_for_button;
    std::vector<std::vector<QWidget*>> m_wgt;
    std::vector<std::vector<std::tuple<QWidget*, QGridLayout*, QString>>> m_widgets;
    std::vector<std::vector<std::pair<uint16_t, uint16_t>>> m_status_changed_edit;
    std::vector<std::vector<std::pair<uint16_t, uint16_t>>> m_status_changed_table;
    std::vector<std::vector<QLabel*>> m_lb_name_command;
    std::vector<std::vector<QLineEdit*>> m_le_edit_command;
    void add_edit(uint16_t num_bokz, const QString& name_param,
                  const QString& key, const uint16_t& name_to_send);

    std::vector<std::vector<QTableWidget*>> m_tables;
    void add_table(uint16_t num_bokz, uint16_t row, uint16_t collumn,
                   const QString& name_param, const QString& key, const uint16_t& name_to_send);
    std::vector<int16_t> m_edit_count;
    std::vector<int16_t> m_table_count;

    std::map<QString, uint16_t> m_dict_type_command_for_load;

    std::map<QString, std::array<uint16_t, 2>> m_dict_for_table_size;
    void create_template_for_table();
};

#endif // KIA_OPTIONS_COMMAND_H
