#include "save_read_settings.h"

Save_read_settings::Save_read_settings(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{
}

Save_read_settings::~Save_read_settings()
{
    save_settings();
}

void Save_read_settings::save_settings()
{
    QStringList list_used_bokz;
    QStringList list_mpi_num;
    QStringList list_address_change;
    QStringList list_lpi_change;
    QStringList list_do_mpi_command;
    QStringList list_do_count_cyclogram;
    QStringList list_do_cyclogram_tp;
    QStringList list_do_cyclogram_ai;
    QStringList list_tp_param;
    QStringList list_zkr_param;
    QStringList list_frames_param;
    QStringList list_used_bi;
    QStringList list_used_channel;
    QStringList list_ai_settings_is_continue;
    QStringList list_power_after_tp;

    for (uint16_t mpi_command = 0; mpi_command < m_kia_settings->m_kia_bokz_settings->m_max_mpi_command; ++mpi_command)
        list_do_mpi_command.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram[mpi_command]));

    for (uint16_t num_cycl = 0; num_cycl < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp; ++num_cycl)
        list_do_cyclogram_tp.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp[num_cycl]));

    for (uint16_t num_cycl = 0; num_cycl < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_ai; ++num_cycl)
        list_do_cyclogram_ai.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai[num_cycl]));

    for (uint16_t num_cycl = 0; num_cycl < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp; ++num_cycl)
        list_do_count_cyclogram.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_count_to_do_cyclogram_in_tp[num_cycl]));

    for (uint16_t ind_tp_param = 0; ind_tp_param < constants::max_count_param; ++ind_tp_param)
        list_tp_param.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[ind_tp_param]));

    for (uint16_t ind_zkr_param = 0; ind_zkr_param < constants::max_count_param; ++ind_zkr_param)
        list_zkr_param.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[ind_zkr_param]));

    for (uint16_t ind_frames_param = 0; ind_frames_param < constants::max_count_param; ++ind_frames_param)
        list_frames_param.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[ind_frames_param]));

    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        list_used_bokz.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz]));
        list_mpi_num.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_mpi_num_index_of_num_bokz[num_bokz]));
        list_address_change.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_address_change[num_bokz]));
        list_lpi_change.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_lpi_change[num_bokz]));
        list_used_bi.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_num_used_bi[num_bokz]));
        list_used_channel.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_num_used_channel[num_bokz]));
    }

    list_ai_settings_is_continue.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_skip_fails_for_continue));
    list_power_after_tp.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_off_power_for_tp));

    m_settings.beginGroup("/Device_settings_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    m_settings.setValue("/used_mpi_command", QVariant::fromValue(list_do_mpi_command));
    m_settings.setValue("/used_cyclogram", QVariant::fromValue(list_do_cyclogram_tp));
    m_settings.setValue("/list_used_ai_cycl", QVariant::fromValue(list_do_cyclogram_ai));
    m_settings.setValue("/used_do_count_cyclogram", QVariant::fromValue(list_do_count_cyclogram));
    m_settings.setValue("/ai_param_is_continue", QVariant::fromValue(list_ai_settings_is_continue));
    m_settings.setValue("/power_after_tp", QVariant::fromValue(list_power_after_tp));
    m_settings.setValue("/tp_param", QVariant::fromValue(list_tp_param));
    m_settings.setValue("/zkr_param", QVariant::fromValue(list_zkr_param));
    m_settings.setValue("/frames_param", QVariant::fromValue(list_frames_param));
    m_settings.setValue("/used_bokz", QVariant::fromValue(list_used_bokz));
    m_settings.setValue("/mpi_num", QVariant::fromValue(list_mpi_num));
    m_settings.setValue("/list_address_change", QVariant::fromValue(list_address_change));
    m_settings.setValue("/list_lpi_change", QVariant::fromValue(list_lpi_change));
    m_settings.setValue("/mode_kp", QVariant::fromValue(m_kia_settings->m_kia_bi_settings->m_mode_kp));
    m_settings.setValue("/mode_1s", QVariant::fromValue(m_kia_settings->m_kia_bi_settings->m_mode_1s));
    m_settings.setValue("/list_used_bi", QVariant::fromValue(list_used_bi));
    m_settings.setValue("/list_used_channel", QVariant::fromValue(list_used_channel));
    m_settings.endGroup();


    m_settings.beginGroup("/Gui_settings_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    m_settings.setValue("/count_table_state" , QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_status_for_table_state.size()));
    for (uint16_t num_table = 0; num_table < m_kia_settings->m_kia_gui_settings->m_status_for_table_state.size(); ++num_table)
        m_settings.setValue("/status_for_table_state_" + QString::number(num_table), QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_status_for_table_state[num_table]));

    for (uint16_t num_table = 0; num_table < m_kia_settings->m_kia_gui_settings->m_color_for_table_state.size(); ++num_table)
        m_settings.setValue("/color_for_table_state_" + QString::number(num_table), QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_color_for_table_state[num_table]));

    m_settings.setValue("/count_status_for_menu_action", QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_status_for_menu_action.size()));
    for (uint16_t num_menu = 0; num_menu < m_kia_settings->m_kia_gui_settings->m_status_for_menu_action.size(); ++num_menu)
        m_settings.setValue("/status_for_menu_action_" + QString::number(num_menu), QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_status_for_menu_action[num_menu]));

    m_settings.setValue("/status_for_menu_for_menubar", QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_status_menu_from_menubar));

    m_settings.endGroup();
    save_tabs_settings();
    save_graph_settings();
    save_table_settings();
    save_profile_settings();
}

void Save_read_settings::load_settings()
{
    bool do_load = true;
    m_settings.beginGroup("/Device_settings_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    auto keys_dev = m_settings.allKeys();
    if (keys_dev.size() != 0)
    {
        QStringList list_do_mpi_command;
        list_do_mpi_command = m_settings.value("/used_mpi_command").value<QStringList>();

        QStringList list_do_count_cyclogram;
        list_do_count_cyclogram = m_settings.value("/used_do_count_cyclogram").value<QStringList>();

        QStringList list_do_cyclogram;
        list_do_cyclogram = m_settings.value("/used_cyclogram").value<QStringList>();

        QStringList list_zkr_param;
        list_zkr_param = m_settings.value("/zkr_param").value<QStringList>();

        QStringList list_tp_param;
        list_tp_param = m_settings.value("/tp_param").value<QStringList>();

        QStringList list_frames_param;
        list_frames_param = m_settings.value("/frames_param").value<QStringList>();

        QStringList list_used_bokz;
        list_used_bokz = m_settings.value("/used_bokz").value<QStringList>();

        QStringList list_mpi_num;
        list_mpi_num = m_settings.value("/mpi_num").value<QStringList>();

        QStringList list_ai_settings_is_continue;
        list_ai_settings_is_continue = m_settings.value("/ai_param_is_continue").value<QStringList>();

        QStringList list_power_after_tp;
        list_power_after_tp = m_settings.value("/power_after_tp").value<QStringList>();

        QStringList list_address_change;
        list_address_change = m_settings.value("/list_address_change").value<QStringList>();

        QStringList list_lpi_change;
        list_lpi_change = m_settings.value("/list_lpi_change").value<QStringList>();

        m_kia_settings->m_kia_bi_settings->m_mode_kp = m_settings.value("/mode_kp").value<quint16>();

        m_kia_settings->m_kia_bi_settings->m_mode_1s = m_settings.value("/mode_1s").value<quint16>();

        QStringList list_used_bi;
        list_used_bi = m_settings.value("/list_used_bi").value<QStringList>();

        QStringList list_used_channel;
        list_used_channel = m_settings.value("/list_used_channel").value<QStringList>();
        if (list_used_bokz.size() != m_kia_settings->m_kia_bokz_settings->m_count_bokz)
            do_load = false;

        QStringList list_ai_used_cycl;
        list_ai_used_cycl = m_settings.value("/list_used_ai_cycl").value<QStringList>();

        list_used_bokz.push_front(QString::number(TS_USED_BOKZ));

        list_address_change.push_front(QString::number(TS_ADDRESS));

        list_mpi_num.push_front("load");
        list_mpi_num.push_front(QString::number(TS_MPI));

        list_lpi_change.push_front(QString::number(TS_LPI));

        list_used_bi.push_front("load");
        list_used_bi.push_front(QString::number(TS_TYPE_BI));

        list_used_channel.push_front("load");
        list_used_channel.push_front(QString::number(TS_NUM_CH));

        emit send_to_kia_options(KNCycl_AI, list_ai_settings_is_continue);
        emit send_to_kia_options(KNCycl_REGULAR, list_do_mpi_command);
        emit send_to_kia_options(KNCycl_TR, list_tp_param);
        emit send_to_kia_options(KNCycl_ZKR, list_zkr_param);
        emit send_to_kia_options(KNCycl_FRAMES, list_frames_param);
        emit send_to_kia_options(KNCycl_AI_USED_CYCL, list_ai_used_cycl);

        emit send_to_tp_cyclogram_settings(USED_CYCLOGRAM, list_do_cyclogram);
        emit send_to_tp_cyclogram_settings(COUNT_TO_DO_CYCLOGRAM, list_do_count_cyclogram);
        emit send_to_tp_cyclogram_settings(OFF_POWER, list_power_after_tp);
        if (do_load)
        {
            emit send_to_table_settings_window(list_used_bokz);
            emit send_to_table_settings_window(list_mpi_num);
            emit send_to_table_settings_window(list_address_change);
            emit send_to_table_settings_window(list_lpi_change);
            emit send_to_table_settings_window(list_used_bi);
            emit send_to_table_settings_window(list_used_channel);
        }
    }
    else
        std::cout <<"empty ini dev settings" << std::endl;
    m_settings.endGroup();

    m_settings.beginGroup("/Gui_settings_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    auto keys_gui = m_settings.allKeys();
    if (keys_gui.size() != 0)
    {
        auto count_table_state = m_settings.value("/count_table_state").value<quint16>();
        for (uint16_t num_table = 0; num_table < count_table_state; ++num_table)
        {
            auto list_status = m_settings.value("/status_for_table_state_" + QString::number(num_table)).value<QStringList>();
            emit send_list_for_check_box_table_state(num_table, list_status);

            auto list_color = m_settings.value("/color_for_table_state_" + QString::number(num_table)).value<QStringList>();
            emit send_list_for_check_box_color_table_state(num_table, list_color);
        }
        auto count_menu = m_settings.value("/count_status_for_menu_action").value<quint16>();

        for (uint16_t num_menu = 0; num_menu < count_menu; num_menu++)
        {
            auto list_actions = m_settings.value("/status_for_menu_action_" + QString::number(num_menu)).value<QStringList>();
            //std::cout << list_actions.size() << std::endl;
            emit send_list_for_menu_actions(num_menu, list_actions);
        }
        auto list_actions = m_settings.value("/status_for_menu_for_menubar").value<QStringList>();
        emit send_to_list_for_check_box_menu_for_menubar(list_actions);
    }
    else
        std::cout <<"empty ini gui settings" << std::endl;
    m_settings.endGroup();

}

void Save_read_settings::load_graph_settings()
{
    m_settings.beginGroup("/Graph_settings_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    if (m_settings.allKeys().size() != 0)
    {

        QStringList  used_graph;
        m_kia_settings->m_kias_view_data->m_graph_count = m_settings.value("/count_graphs").value<uint16_t>();
        used_graph = m_settings.value("/graph_index").value<QStringList>();
        for (auto el : used_graph)
        {
            auto graph_set = m_settings.value("/graph_" + el).value<QStringList>();
            m_kia_settings->m_kias_view_data->m_data_graph.push_back(graph_set);
            emit send_to_plot_contructor(graph_set);
        }
    }
    else
        std::cout <<"empty ini settings graph" << std::endl;
    m_settings.endGroup();
}

void Save_read_settings::save_graph_settings()
{
    m_settings.beginGroup("/Graph_settings_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    QStringList  used_graph;
    for (uint16_t num_graph = 0; num_graph < m_kia_settings->m_kias_view_data->m_data_graph.size(); num_graph++)
    {
        m_settings.setValue("/graph_" + m_kia_settings->m_kias_view_data->m_data_graph[num_graph][QP_NUM_WIDGET], QVariant::fromValue(m_kia_settings->m_kias_view_data->m_data_graph[num_graph]));
        used_graph.push_back(m_kia_settings->m_kias_view_data->m_data_graph[num_graph][QP_NUM_WIDGET]);
    }
    m_settings.setValue("/graph_index" , QVariant::fromValue(used_graph));
    m_settings.setValue("/count_graphs" , QVariant::fromValue(m_kia_settings->m_kias_view_data->m_graph_count));
    m_settings.endGroup();
}

void Save_read_settings::load_table_settings()
{
    m_settings.beginGroup("/Table_settings" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    if (m_settings.allKeys().size() != 0)
    {

        QStringList  used_table;
        m_kia_settings->m_kias_view_data->m_table_count = m_settings.value("/count_tables").value<uint16_t>();
        used_table = m_settings.value("/table_index").value<QStringList>();
        for (auto el : used_table)
        {
            auto table_set = m_settings.value("/table_" + el).value<QStringList>();
            auto table_cols_set = m_settings.value("/table_cols_" + el).value<QStringList>();
            m_kia_settings->m_kias_view_data->m_data_table.push_back(table_set);
            m_kia_settings->m_kias_view_data->m_data_table_cols.push_back(table_cols_set);
            table_cols_set.pop_front();
            emit send_to_table_constructor(table_set, table_cols_set);
        }
    }
    else
        std::cout <<"empty ini settings_table" << std::endl;
    m_settings.endGroup();
}

void Save_read_settings::save_table_settings()
{
    m_settings.beginGroup("/Table_settings" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    QStringList  used_table;
    for (uint16_t num_table = 0; num_table < m_kia_settings->m_kias_view_data->m_data_table.size(); num_table++)
    {
        m_settings.setValue("/table_" + m_kia_settings->m_kias_view_data->m_data_table[num_table][QP_NUM_WIDGET], QVariant::fromValue(m_kia_settings->m_kias_view_data->m_data_table[num_table]));
        m_settings.setValue("/table_cols_" + m_kia_settings->m_kias_view_data->m_data_table_cols[num_table][0], QVariant::fromValue(m_kia_settings->m_kias_view_data->m_data_table_cols[num_table]));
        used_table.push_back(m_kia_settings->m_kias_view_data->m_data_table[num_table][QP_NUM_WIDGET]);
    }
    m_settings.setValue("/table_index" , QVariant::fromValue(used_table));
    m_settings.setValue("/count_tables" , QVariant::fromValue(m_kia_settings->m_kias_view_data->m_table_count));
    m_settings.endGroup();
}

void Save_read_settings::load_tabs_settings()
{
    m_settings.beginGroup("/Tabs_settings" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    if (m_settings.allKeys().size() != 0)
    {
        m_kia_settings->m_kia_gui_settings->m_count_tab_bar = m_settings.value("/count_tabs").value<uint16_t>();
        QStringList  used_tabs;
        used_tabs = m_settings.value("/tab_index").value<QStringList>();
        for (auto el : used_tabs)
        {
            auto tab_set = m_settings.value("/tab_" + el).value<QStringList>();
            m_kia_settings->m_kia_gui_settings->m_data_tabs.push_back(tab_set);
            emit send_list_to_add_tab(tab_set);
        }

        auto current_main_tab_index = m_settings.value("/current_main_tab_index").value<quint16>();
        emit send_current_main_tab_widget(current_main_tab_index);
    }
    else
        std::cout <<"empty ini settings_tabs" << std::endl;
    m_settings.endGroup();
}

void Save_read_settings::save_tabs_settings()
{
    m_settings.beginGroup("/Tabs_settings" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    m_settings.setValue("/current_main_tab_index" , QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget));
    QStringList  used_tab;
    for (uint16_t num_tab = 0; num_tab < m_kia_settings->m_kia_gui_settings->m_data_tabs.size(); num_tab++)
    {
        m_settings.setValue("/tab_" + m_kia_settings->m_kia_gui_settings->m_data_tabs[num_tab][NUM_TAB], QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_data_tabs[num_tab]));
        used_tab.push_back(m_kia_settings->m_kia_gui_settings->m_data_tabs[num_tab][NUM_TAB]);
    }
    m_settings.setValue("/tab_index" , QVariant::fromValue(used_tab));
    m_settings.setValue("/count_tabs" , QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_count_tab_bar));

    m_settings.endGroup();
}

void Save_read_settings::load_profile_settings()
{
    m_settings.beginGroup("/Profile_settings");
    if (m_settings.allKeys().size() != 0)
    {

        QStringList  used_profile;
        m_kia_settings->m_current_profile = m_settings.value("/last_profile").value<uint16_t>();
        m_kia_settings->m_kia_gui_settings->m_count_profile = m_settings.value("/count_profiles").value<uint16_t>();
        used_profile = m_settings.value("/profile_index").value<QStringList>();
        for (auto el : used_profile)
        {
            auto profile_set = m_settings.value("/profile_" + el).value<QStringList>();
            m_kia_settings->m_kia_gui_settings->m_list_profile.push_back(profile_set);
            emit send_to_kia_profile(profile_set);
        }
    }
    else
        std::cout <<"empty ini settings profile" << std::endl;
    m_settings.endGroup();
}

void Save_read_settings::save_profile_settings()
{
    m_settings.beginGroup("/Profile_settings");
    QStringList  used_profile;
    for (uint16_t num_profile = 0; num_profile < m_kia_settings->m_kia_gui_settings->m_list_profile.size(); num_profile++)
    {
        m_settings.setValue("/profile_" + m_kia_settings->m_kia_gui_settings->m_list_profile[num_profile][NUM_PROFILE],
                            QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_list_profile[num_profile]));
        used_profile.push_back(m_kia_settings->m_kia_gui_settings->m_list_profile[num_profile][NUM_PROFILE]);
    }
    m_settings.setValue("/profile_index" , QVariant::fromValue(used_profile));
    m_settings.setValue("/count_profiles" , QVariant::fromValue(m_kia_settings->m_kia_gui_settings->m_count_profile));
    m_settings.setValue("/last_profile" , QVariant::fromValue(m_kia_settings->m_current_profile));
    m_settings.endGroup();
}


void Save_read_settings::save_pos_and_size_widgets(const QString save_name, QWidget *wgt)
{
    m_settings.beginGroup("/Window_save_geometry_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    m_settings.setValue("/geometry_" + save_name, wgt->saveGeometry());
    m_settings.endGroup();
}

void Save_read_settings::load_pos_and_size_widgets(const QString save_name, QWidget *wgt)
{

    m_settings.beginGroup("/Window_save_geometry_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    wgt->restoreGeometry(m_settings.value("/geometry_" + save_name).toByteArray());
    auto curr_pos = QPoint((int)(wgt->pos().x() / constants::max_grid_size) * constants::max_grid_size,
                           (int)(wgt->pos().y() / constants::max_grid_size) * constants::max_grid_size);
    wgt->move(curr_pos);
    m_settings.endGroup();
}

void Save_read_settings::save_state_widgets(const QString save_name, QWidget *wgt)
{
    m_settings.beginGroup("/Window_save_state_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    m_settings.setValue("/title_" + save_name, wgt->windowTitle());
    m_settings.setValue("/num_parent_" + save_name, m_kia_settings->m_kia_gui_settings->m_current_num_parent.value(wgt));
    m_settings.setValue("/is_hide_" + save_name, m_kia_settings->m_kia_gui_settings->m_widget_is_hide.value(wgt));
    m_settings.endGroup();
}

void Save_read_settings::load_state_widgets(const QString save_name, QWidget *wgt, bool is_window_info)
{
    m_settings.beginGroup("/Window_save_state_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    wgt->setWindowTitle(m_settings.value("/title_" + save_name).value<QString>());
    m_kia_settings->m_kia_gui_settings->m_widget_is_hide[wgt] = m_settings.value("/is_hide_" + save_name).value<bool>();
    m_kia_settings->m_kia_gui_settings->m_current_num_parent[wgt] = m_settings.value("/num_parent_" + save_name).value<int16_t>();
    if (is_window_info)
    {
        if (m_kia_settings->m_kia_gui_settings->m_current_num_parent[wgt] == -1)
        {
            emit set_default_parent(wgt);

        }
        else
            wgt->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_num_parent[wgt]]);
    }
    if (m_kia_settings->m_kia_gui_settings->m_widget_is_hide.value(wgt))
    {

        wgt->show();
    }
    else
    {
        wgt->hide();
    }

    m_settings.endGroup();
}

void Save_read_settings::save_state_dock_manager(CDockManager *manager)
{
    m_settings.beginGroup("/Docker_save_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    m_settings.setValue("/dock_manager", manager->saveState());
    m_settings.endGroup();
}

void Save_read_settings::load_state_dock_manager(CDockManager *manager)
{
    m_settings.beginGroup("/Docker_save_" + QString("type_profile_") + QString::number(m_kia_settings->m_current_profile)
                          + QString("_type_bokz_") + QString::number(m_kia_settings->m_type_bokz));
    manager->restoreState(m_settings.value("/dock_manager").toByteArray());
    m_settings.endGroup();
}
