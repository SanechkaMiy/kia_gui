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
const static uint16_t max_mpi_command = 5;
const static uint16_t max_count_mpi = MAX_TMK_NUMBER * 2 + 1;
const static uint16_t max_count_window = 1;
const static uint16_t size_qa = 4;
const static uint16_t size_w = 3;
const static uint16_t max_count_cyclograms = 5;
const static uint16_t max_count_param = 3;
const static uint16_t max_count_relay_command = 3;
const static uint16_t max_count_bi_settings = 2;
const static uint16_t max_count_name_command = 3;
const static uint16_t max_grid_size = 25;
}

#pragma pack(push, 1)
struct Kia_data_to_server
{
    std::array<uint16_t, constants::max_mpi_command> m_do_mpi_command_in_cyclogram;
    std::vector<int> m_is_used_bokz;
    std::vector<int> m_mpi_num;
    std::vector<int> m_mpi_num_index_of_num_bokz;
    std::vector<int> m_address_change;
    std::vector<int> m_td_change;
    std::vector<int> m_lpi_change;
    std::vector<float> m_qa;
    std::vector<float> m_w;
    int m_bshv;
    std::array<uint16_t, constants::max_count_param> m_param_for_cycl_zkr;
    std::array<uint16_t, constants::max_count_param> m_param_for_cycl_full_frames;
    std::array<uint16_t, constants::max_count_param> m_param_for_cycl_tech_run;
    int m_1s_mark_change;
    uint16_t m_skip_fails_for_continue = 1;
    std::array<uint16_t, constants::max_count_relay_command> m_param_relay_command;
    std::vector<int> m_num_used_bi;
    std::vector<int> m_num_used_channel;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kia_bi_settings
{
    std::array<QString, constants::count_type_bi> m_bi_type = {"БКПИК", "БИУ"};//0 - БКПИК; 1 - БИ; 2 - БИУ; 3 - БИНК; 4 - БКПИКМ.
    std::array<int, constants::count_type_bi> m_bi_count_channel = {3, 2};//0 - БКПИК; 1 - БИ; 2 - БИУ; 3 - БИНК; 4 - БКПИКМ.
    int m_count_bi;//0 - БКПИК; 1 - БИ; 2 - БИУ; 3 - БИНК; 4 - БКПИКМ.
    std::array<QStringList, constants::count_type_bi> m_bi_row_name;
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
    int m_count_bokz;//0 - БОКЗМ60; 1 - БОКЗМ60/1000; 2 - БОКЗМР; 3 - АИС-2К; 4 - БОКЗНК.
    std::array<QStringList, constants::count_type_bokz> m_bokz_row_name;
    std::array<QStringList, constants::count_type_bokz> m_bokz_status_row_name;
    std::array<QString, constants::max_count_cyclograms> m_name_cyclograms =
    {
        {"Автономные испытания", "Штатная", "Технологический прогон", "Испытание крышки", "Получение кадров"}//,{"dr..."}
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
    QStringList m_mpi_command_name = {"ШТМИ1", "ШТМИ2", "МШИОР", "ДТМИ", "ДТМИ-ЛОК"};
    std::vector<QStringList> m_list_profile;
    uint16_t m_count_profile = 0;
    uint16_t m_current_main_tab_widget = 0;
    QMap<QWidget*, int16_t> m_current_num_parent;
    std::vector<QStringList> m_status_for_table_state;
    std::vector<QStringList> m_color_for_table_state;
    std::vector<QStringList> m_status_for_menu_action;
    std::vector<QStringList> m_debug_comand_param;
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
    std::vector<QStringList> m_data_graph;
    std::vector<QStringList> m_data_table;
    std::vector<QStringList> m_data_table_cols;
    QMap<uint16_t, QStringList> m_data_graph_on_tabs;
    QMap<uint16_t, QStringList> m_data_tables_on_tabs;
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
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kias_data_from_db
{
    QVector<QVariant> m_x_value;
    QVector<QVariant> m_y_value;
    QVector<QVariant> m_date_time_val;
    std::queue<QSqlQueryModel*> m_model;
    std::atomic_bool m_is_main_graph{false};
    std::atomic_bool m_is_default_graph{false};
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
        m_kia_bi_settings->m_bi_row_name[TYPE_BI_BKPIK] << "КС" << "КП" << "ТД" << "1С";
        m_kia_bi_settings->m_bi_row_name[TYPE_BI_BIU] << "БИ-У" << "КС" << "КРР" << "БРТУЗ" << "КП" << "БТВК"
                                                      << "ИП" << "БТВП"
                                                      << "ПИТ1" << "ПИТ2"
                                                      << "ИЗН1"  << "ИЗН2" << "ТД"
                                                      << "1С";
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
