#ifndef KIACORE_H
#define KIACORE_H

#include <QObject>
#include <QMenuBar>
#include <QDialog>
#include <QFont>
#include <iostream>
#include <client.h>
#include "kiamenubar.h"
#include "kia_main_window.h"
#include "Kia_main_struct.h"
#include "kiawindowinfo.h"
#include "kiawindowstate.h"
#include "kiawindowsettings.h"
#include "kiawindowiswork.h"
#include "save_read_settings.h"
#include "kia_options_cyclograms.h"
#include "kia_options_command.h"
#include "kia_profile.h"
#include "kia_options_bi.h"
#include "kia_graph_manager.h"
#include "kia_table_manager.h"
#include "kia_constructor.h"
#include "kia_options.h"
#include "kia_options_interface.h"
#include <vector>
#include <array>
#include <utility>
class KiaCore : public QObject
{
    Q_OBJECT
public:
    explicit KiaCore(QWidget * wgt = nullptr, QObject *parent = nullptr);
    ~KiaCore();
public slots:
    void create_menubar();
private:
    CDockManager* m_dock_manager;
    std::map<QString, std::vector<uint16_t>> m_keys_for_dock_widget;
    QVector<QAction*> m_plot_action;
    QVector<QAction*> m_table_action;
    QVector<QAction*> m_profile_action;
    std::vector<std::pair<QWidget*, QString>> m_kia_options_list;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    std::shared_ptr<Save_read_settings> m_save_read_settings;
    Kia_main_window* m_kia_main_window;
    KiaMenuBar* m_kia_menubar;
    Kia_options* m_kia_options;
    Kia_profile* m_kia_profile;
    std::shared_ptr<Kia_constructor> m_kia_constructor;
    std::shared_ptr<Kia_graph_manager> m_kia_graph_manager;
    std::shared_ptr<Kia_table_manager> m_kia_table_manager;
    Kia_options_cyclograms* m_kia_options_cyclograms;
    Kia_options_bi* m_kia_options_bi;
    Kia_options_command* m_kia_options_command;
    Kia_options_interface* m_kia_options_interface;
    KiaWindowState* m_kia_window_state_for_all_dev;
    KiaWindowSettings* m_kia_window_settings_for_all_dev;
    std::vector<KiaWindowInfo*> m_kia_window_info_system_info;
    std::vector<KiaWindowInfo*> m_kia_window_info_error_info;
    std::vector<KiaWindowInfo*> m_kia_window_info_mpi_for_dev;
    std::vector<KiaWindowInfo*> m_kia_window_info_device_protocol;
    std::vector<KiaWindowInfo*> m_kia_window_info_ai_protocol;
    std::array<std::vector<KiaWindowInfo*>, constants::max_mpi_command> m_kia_window_info_mpi_command;
    KiaWindowInfo* m_kia_window_info_mpi;
    KiaWindowIsWork* m_kia_window_is_work;

    void set_dock_actions(const std::pair<QString, QAction*>& action);

    void create_menu_action();
    void correct_save_state_window(QDialog *window_info);

    void create_kia_profile();

    void create_kia_options();
    void create_kia_options_for_bi_command();
    void create_kia_options_for_cyclogram();
    void create_kia_options_for_command();
    void create_kia_options_for_interface();
private slots:
    void set_mpi_command_for_cyclogram();
    void set_kia_gui_settings_slot();


    void create_kia_graph_manager();
    void create_action_for_graph(QString name_graph, int32_t num_graph);
    void remove_action_from_graph(int32_t num_graph);

    void create_kia_table_manager();
    void create_action_for_table(QString name_graph, int32_t num_table);
    void remove_action_from_table(int32_t num_graph);

    void create_window_mpi();
    void create_window_state(qint16 type_bi);
    void create_window_settings(qint16 type_bokz);
    void create_window_is_work();

    void create_mpi_command_action();
    void create_action_info_mpi_info();
    void create_action_info_mpi_dev_info();
    void create_action_info_ai_info();
    void create_action_info_system_info();
    void create_action_info_error_info();
    void create_action_info_dev();

    void set_data_to_table_state(qint16 type_bi, QStringList data_from_server);
    void set_status_bi_1s_mark(qint16 num_bi);
    void send_data_from_client(qint16 num, QStringList data_for_server);
    void set_window_info_mpi(qint16 type_mpi_dev, QString data_from_server);
    void set_window_info_system_window(qint16 num_bokz, QString data_from_server);
    void set_window_info_ai_window(qint16 num_bokz, QString data_from_server);
    void set_window_info_error_window(qint16 num_bokz, QString data_from_server);
    void set_window_info_device_protocol(qint16 num_mpi_command,qint16 num_bokz, QString data_from_server);
    void set_otclp_stop(qint16 is_otclp);
    void reset_before_load_profile();
    void load_profile_settings();
    void show_kia_profile_slot();
};

#endif // KIACORE_H
