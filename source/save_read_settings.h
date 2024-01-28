#ifndef SAVE_READ_SETTINGS_H
#define SAVE_READ_SETTINGS_H
#include <iostream>
#include "Kia_main_struct.h"
#include "Kia_enums.h"
#include <QWidget>
#include <QSettings>
#include <memory>
#include "DockManager.h"
using namespace ads;
class Save_read_settings : public QObject
{
    Q_OBJECT
public:
    Save_read_settings(std::shared_ptr<Kia_settings> kia_settings);
    ~Save_read_settings();
    void save_settings();
    void load_settings();

    void load_graph_settings();
    void save_graph_settings();

    void load_table_settings();
    void save_table_settings();

    void load_tabs_settings();
    void save_tabs_settings();

    void load_profile_settings();
    void save_profile_settings();

    void save_pos_and_size_widgets(const QString save_name, QWidget* wgt);
    void load_pos_and_size_widgets(const QString save_name, QWidget* wgt);
    void save_state_widgets(const QString save_name, QWidget *wgt);
    void load_state_widgets(const QString save_name, QWidget *wgt, bool is_window_info = true);

    void save_state_dock_manager(CDockManager *manager);
    void load_state_dock_manager(CDockManager *manager);

signals:
    void send_to_table_settings_window(QStringList);
    void send_to_kia_options(qint16, QStringList);
    void send_to_plot_contructor(QStringList);
    void send_to_table_constructor(QStringList, QStringList);
    void send_to_kia_profile(QStringList);
    void send_list_for_check_box_table_state(qint16, QStringList);
    void send_list_for_check_box_color_table_state(qint16, QStringList);
    void send_list_for_menu_actions(qint16, QStringList);
    void send_current_main_tab_widget(uint16_t);
    void send_list_to_add_tab(QStringList);
    void set_default_parent(QWidget*);
    void send_to_tp_cyclogram_settings(qint16, QStringList);
    void send_to_list_for_check_box_menu_for_menubar(QStringList);
    void send_to_regular_cyclogram_do_command(qint16, qint16, QStringList);
    void send_to_power_cyclogram_do_command(qint16, qint16, QStringList);
    void send_to_ri_cyclograms(qint16, QStringList);
    void send_frames_cyclograms(qint16, qint16);
private:
    std::shared_ptr<Kia_settings> m_kia_settings;
    QSettings m_settings;
};

#endif // SAVE_READ_SETTINGS_H
