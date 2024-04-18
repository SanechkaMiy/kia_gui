#ifndef KIA_MAIN_STRUCT_H
#define KIA_MAIN_STRUCT_H
#include <QTime>
#include <iostream>
#include <array>
#include <QStringList>
#include <QVector>
#include <Kia_enums.h>
#include <memory>
#include <QSettings>
#include <QString>
#include <QWidgetList>
#include <QMap>
#include <QAction>
#include <QSqlQueryModel>
#include <QLineEdit>
#include <queue>
#include "DockWidget.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#define PI    3.141592653589793f

using namespace ads;
namespace constants
{
const uint16_t MAX_TMK_NUMBER =  7;
const static uint16_t count_type_bi = 2;
const static uint16_t max_count_bi = 1;
const static uint16_t max_count_lpi = 2;
const static uint16_t count_type_bokz = 6;
const static uint16_t max_count_channel = 4;
const static uint16_t max_count_address = 32;
const static uint16_t max_count_td = 6;
const static uint16_t max_count_mpi = MAX_TMK_NUMBER * 2 + 1;
const static uint16_t max_count_window = 1;
const static uint16_t size_qa = 4;
const static uint16_t size_w = 3;
const static uint16_t max_count_cyclograms = 3;
const static uint16_t max_count_param = 3;
const static uint16_t max_count_relay_command = 3;
const static uint16_t max_count_bi_settings = 2;
const static uint16_t max_count_name_command = 3;
const static uint16_t max_grid_size = 25;
}

#pragma pack(push, 1)
struct Kia_data_to_server
{
    std::vector<uint16_t> m_do_mpi_command_in_cyclogram;
    std::vector<uint16_t> m_do_cyclogram_in_tp;
    std::vector<uint16_t> m_do_cyclogram_in_ai;

    std::vector<std::vector<uint16_t>> m_do_cyclograms_in_do;
    std::vector<std::vector<uint64_t>> m_pause_to_do_cyclogram_in_do;

    std::vector<uint16_t> m_count_to_do_cyclogram_in_tp;

    std::vector<std::vector<uint16_t>> m_do_cyclograms_power_in_do;

    std::vector<int> m_is_used_bokz;
    std::vector<int> m_mpi_num;
    std::vector<int> m_mpi_num_index_of_num_bokz;
    std::vector<int> m_address_change;
    std::vector<int> m_td_change;
    std::vector<int> m_lpi_change;
    std::vector<float> m_qa;
    std::vector<float> m_w;
    int m_bshv;
    std::vector<std::array<float, constants::max_count_param>> m_param_for_run_a_lot;
    int m_1s_mark_change;
    uint16_t m_skip_fails_for_continue = 1;
    uint16_t m_off_power_for_tp = 0;
    std::array<uint16_t, constants::max_count_relay_command> m_param_relay_command;
    std::vector<int> m_num_used_bi;
    std::vector<int> m_num_used_channel;


    uint16_t m_frame_type_recieve;
    uint16_t m_frame_type;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kia_bi_settings
{
    uint16_t m_bi_is_used {CS_IS_OFF};
    std::array<QString, constants::count_type_bi> m_bi_type = {"БКПИК", "БИ-У"};//0 - БКПИК; 1 - БИ; 2 - БИУ; 3 - БИНК; 4 - БКПИКМ.
    std::array<int, constants::count_type_bi> m_bi_count_channel = {3, 2};//0 - БКПИК; 1 - БИ; 2 - БИУ; 3 - БИНК; 4 - БКПИКМ.
    int m_count_bi;//0 - БКПИК; 1 - БИ; 2 - БИУ; 3 - БИНК; 4 - БКПИКМ.
    QStringList m_bi_data;
    int m_sec_mark_period;
    uint16_t m_mode_kp = 3;
    uint16_t m_mode_1s = 3;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kia_bokz_settings
{
    int m_freq_bokz;
    std::array<QString, constants::count_type_bokz> m_bokz_type = {"БОКЗМ60", "БОКЗМФ"};
    std::array<QString, constants::count_type_bokz> m_kia_title_type = {"СПО КИА БОКЗ-М60", "БОКЗМФ"};
    int m_count_bokz;//0 - БОКЗМ60; 1 - БОКЗМ60/1000; 2 - БОКЗМР; 3 - АИС-2К; 4 - БОКЗНК.
    uint16_t m_max_mpi_command;
    uint16_t m_max_other_mpi_command;
    uint16_t m_max_cyclograms_in_ai;
    uint16_t m_max_cyclograms_in_tp;
    uint16_t m_max_cyclograms_in_ri;
    std::array<QStringList, constants::count_type_bokz> m_bokz_row_name;
    std::array<QStringList, constants::count_type_bokz> m_bokz_status_row_name;
    std::array<QString, constants::max_count_cyclograms> m_name_cyclograms =
    {
        {"Автономные испытания", "Штатная", "Питание"}//,{"dr..."}
    };
    std::vector<int> m_epsilon;
    std::vector<float> m_focus;
    std::vector<int> m_texp;

};
#pragma pack(pop)


#pragma pack(push, 1)
struct Kia_gui_settings
{
    bool m_widget_is_closed = false;
    QMap<QWidget*, bool> m_widget_is_hide;
    QVector<std::pair<QString, uint16_t>> m_mpi_command_name;
    QVector<std::pair<QString, uint16_t>> m_mpi_other_command_name;

    QVector<std::pair<QString, uint16_t>> m_cyclogram_ai_name;
    QVector<std::pair<QString, uint16_t>> m_cyclogram_tp_name;
    QVector<std::pair<QString, uint16_t>> m_cyclogram_ri_name;
    QVector<std::pair<QString, uint16_t>> m_cyclogram_power_name;

    QVector<std::pair<QString, uint16_t>> m_func_type_frames;
    QVector<QString> m_func_type_frame_recieve;

    std::vector<std::tuple<QString, QString, uint16_t, uint16_t>> m_commands_to_pn;

    std::vector<QVector<std::pair<QString, uint16_t>>> m_cyclogram_do_name;
    std::vector<QVector<std::pair<QString, uint16_t>>> m_cyclogram_power_do_name;

    std::vector<QStringList> m_list_profile;
    uint16_t m_count_profile = 0;
    uint16_t m_current_main_tab_widget = 0;
    QMap<QWidget*, int16_t> m_current_num_parent;
    std::vector<QStringList> m_status_for_table_state;
    std::vector<QStringList> m_color_for_table_state;
    std::vector<QStringList> m_status_for_menu_action;
    std::vector<QStringList> m_debug_comand_param;
    QStringList m_status_menu_from_menubar;
    std::vector<QStringList> m_word_data_param;
    std::vector<CDockWidget*> m_dock_widget;
    std::vector<QWidget*> m_main_tabs_widgets;
    std::vector<QStringList> m_data_tabs;
    uint16_t m_count_tab_bar;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kias_view_data
{
    double m_x_size = 8;
    double m_y_size = 1;
    std::atomic_bool m_is_change_range{true};
    std::atomic_bool m_is_stop_graph{true};
    std::vector<QStringList> m_data_graph;
    std::vector<QStringList> m_data_table;
    std::vector<QStringList> m_data_table_cols;
    uint16_t m_graph_count = 0;
    uint16_t m_table_count = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kias_db
{
    std::array<QString, constants::count_type_bokz> m_bokz_type = {"bokzm60", "bokzmf"};
    std::array<QString, constants::count_type_bi> m_bi_type = {"bkpik", "biu"};//0 - БКПИК; 1 - БИ; 2 - БИУ; 3 - БИНК; 4 - БКПИКМ.
    QString m_experiment_id;
    QTime m_begin;
    QTime m_end;
    double m_key = 0;
    double m_interval_db_exchange = 0.5;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kias_data_from_db
{
    QVector<QVariant> m_x_value;
    QVector<QVariant> m_y_value;
    QVector<QVariant> m_date_time_val;
    QVector<QString> m_data_to_view;
    std::queue<QSqlQueryModel*> m_model;
    int16_t m_graph_type = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kia_settings
{
    Kia_settings()
    {
        m_kia_bi_settings.reset(new Kia_bi_settings());
        m_kia_bokz_settings.reset(new Kia_bokz_settings());
        m_kia_gui_settings.reset(new Kia_gui_settings());
        m_kia_data_to_server.reset(new Kia_data_to_server());
        m_kias_db.reset(new Kias_db());
        m_kias_view_data.reset(new Kias_view_data());
        //        m_kia_bi_settings->m_bi_row_name[TYPE_BI_BKPIK] << "КС" << "КП" << "ТД" << "1С";
    }
    std::shared_ptr<Kia_bi_settings> m_kia_bi_settings;
    std::shared_ptr<Kia_bokz_settings> m_kia_bokz_settings;
    std::shared_ptr<Kia_gui_settings> m_kia_gui_settings;
    std::shared_ptr<Kia_data_to_server> m_kia_data_to_server;
    std::shared_ptr<Kias_db> m_kias_db;
    std::shared_ptr<Kias_view_data> m_kias_view_data;
    uint16_t m_type_bokz;
    uint16_t m_type_bi;
    uint16_t m_is_con_to_db = CS_IS_OFF;
    uint16_t m_is_con_to_core = CS_IS_OFF;
    uint16_t m_current_profile;
};
#pragma pack(pop)
#endif // KIA_MAIN_STRUCT_H
