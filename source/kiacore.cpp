#include "kiacore.h"

KiaCore::KiaCore(QWidget *wgt, QObject *parent)
    : QObject{parent}
    , m_kia_settings(new Kia_settings())
    , m_client(new Client("localhost", 2529, m_kia_settings))
    , m_save_read_settings(new Save_read_settings(m_kia_settings))
    , m_kia_main_window(new Kia_main_window(m_kia_settings, wgt))
    , m_kia_menubar(new KiaMenuBar(m_kia_settings, m_client, m_kia_main_window))
{
    connect(m_client.get(), SIGNAL(set_kia_gui_settings()), this, SLOT(set_kia_gui_settings_slot()));
    connect(m_client.get(), &Client::load_profile, this, [this]()
    {
        load_profile_settings();

    });
    connect(m_kia_menubar, SIGNAL(show_kia_profile()), this, SLOT(show_kia_profile_slot()));
    connect(m_save_read_settings.get(), SIGNAL(send_current_main_tab_widget(uint16_t)), m_kia_main_window, SLOT(set_current_index_tab_widget(uint16_t)));
    connect(m_save_read_settings.get(), SIGNAL(send_list_to_add_tab(QStringList)), m_kia_main_window, SLOT(add_tab_bar_slot(QStringList)));
    connect(m_save_read_settings.get(), &Save_read_settings::set_default_parent, this, [this](QWidget* wgt)
    {
        wgt->hide();
        wgt->setParent(m_kia_main_window);
        m_kia_settings->m_kia_gui_settings->m_current_num_parent[wgt] = -1;
        m_kia_settings->m_kia_gui_settings->m_widget_is_hide[wgt] = wgt->isVisible();
    });

    connect(m_kia_main_window, &Kia_main_window::send_to_change_parent, this, [this](QWidget* wgt)
    {
        wgt->hide();
        wgt->setParent(m_kia_main_window);
        m_kia_settings->m_kia_gui_settings->m_current_num_parent[wgt] = -1;
        m_kia_settings->m_kia_gui_settings->m_widget_is_hide[wgt] = wgt->isVisible();
        std::cout << "set default parent" << std::endl;
    });
    m_kia_main_window->setWindowTitle(m_kia_settings->m_kia_bokz_settings->m_kia_title_type[m_kia_settings->m_type_bokz]);
    m_dock_manager = m_kia_main_window->create_dock_widget(m_kia_main_window);
    m_kia_main_window->set_menu_bar(m_kia_menubar);

}

KiaCore::~KiaCore()
{
    m_save_read_settings->save_pos_and_size_widgets("m_kia_main_window", m_kia_main_window);

    m_save_read_settings->save_pos_and_size_widgets("m_kia_options", m_kia_options);

    m_save_read_settings->save_pos_and_size_widgets("table_state", m_kia_window_state_for_all_dev);

    m_save_read_settings->save_pos_and_size_widgets("table_settings", m_kia_window_settings_for_all_dev);

    m_save_read_settings->save_pos_and_size_widgets("window_is_work", m_kia_window_is_work);

    m_save_read_settings->save_pos_and_size_widgets("kia_debug_commands", m_kia_debug_commands);

    m_save_read_settings->save_pos_and_size_widgets("mpi_all_dev", m_kia_custom_dialog[WINDOW_MPI][0]);
    m_save_read_settings->save_state_widgets("mpi_all_dev", m_kia_custom_dialog[WINDOW_MPI][0]);

    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        m_save_read_settings->save_state_widgets("mpi_for_dev_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]);
        m_save_read_settings->save_state_widgets("device_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]);
        m_save_read_settings->save_state_widgets("system_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]);
        m_save_read_settings->save_state_widgets("error_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]);
        m_save_read_settings->save_state_widgets("ai_protocol_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]);

        m_save_read_settings->save_pos_and_size_widgets("mpi_for_dev_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]);
        m_save_read_settings->save_pos_and_size_widgets("device_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]);
        m_save_read_settings->save_pos_and_size_widgets("system_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]);
        m_save_read_settings->save_pos_and_size_widgets("error_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]);
        m_save_read_settings->save_pos_and_size_widgets("ai_protocol_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]);
    }

    for (uint16_t num_mpi_command = 0; num_mpi_command < m_kia_settings->m_kia_bokz_settings->m_max_mpi_command; ++num_mpi_command)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
        {
            m_save_read_settings->save_state_widgets("mpi_command_wnd_" + QString::number(num_mpi_command) + "_" + QString::number(num_bokz),
                                                     m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]);
            m_save_read_settings->save_pos_and_size_widgets("mpi_command_wnd_" + QString::number(num_mpi_command) + "_" + QString::number(num_bokz),
                                                            m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]);
        }
    }
    auto graph_widget_list = m_kia_graph_manager->get_graph_widgets();
    for (uint16_t num_widget = 0; num_widget < graph_widget_list.size(); ++num_widget)
    {
        m_save_read_settings->save_pos_and_size_widgets("graph_" + QString::number(num_widget), graph_widget_list[num_widget]);
        m_save_read_settings->save_state_widgets("graph_" + QString::number(num_widget), graph_widget_list[num_widget]);
    }

    auto table_widget_list = m_kia_table_manager->get_table_widgets();
    for (uint16_t num_widget = 0; num_widget < table_widget_list.size(); ++num_widget)
    {
        m_save_read_settings->save_pos_and_size_widgets("table_" + QString::number(num_widget), table_widget_list[num_widget]);
        m_save_read_settings->save_state_widgets("table_" + QString::number(num_widget), table_widget_list[num_widget]);
    }
    m_save_read_settings->save_state_dock_manager(m_dock_manager);
}


void KiaCore::create_menubar()
{
    m_kia_menubar->create_actions();
}

void KiaCore::set_dock_actions(const std::pair<QString, QAction *> &action)
{
    for (auto& num_window : m_keys_for_dock_widget[action.first])
        m_kia_settings->m_kia_gui_settings->m_dock_widget[num_window]->setToggleViewAction(action.second);
}

void KiaCore::create_menu_action()
{
    m_kia_menubar->get_menu_settings()->addAction("Настройки", m_kia_menubar, [this]()
    {
        m_kia_options->setWindowTitle("Настройки");
        m_kia_options->show();
    });

    create_mpi_command_action();

    m_kia_menubar->get_menu_windows()->addSeparator();
    auto state_action = m_kia_menubar->get_menu_windows()->addAction("Окно состояния", m_kia_menubar, [this]()
    {
        m_kia_window_state_for_all_dev->show();
    });
    set_dock_actions(std::make_pair("window_state", state_action));

    auto action_param_dev = m_kia_menubar->get_menu_windows()->addAction("Окно параметров прибора", m_kia_menubar, [this]()
    {
        m_kia_window_settings_for_all_dev->show();

    });
    set_dock_actions(std::make_pair("window_param_dev", action_param_dev));

    auto action_state_work = m_kia_menubar->get_menu_windows()->addAction("Окно статус работы", m_kia_menubar, [this]()
    {
        m_kia_window_is_work->show();
    });
    set_dock_actions(std::make_pair("window_state_work", action_state_work));


    create_action_info_system_info();
    create_action_info_dev();
    create_action_info_mpi_info();
    create_action_info_mpi_dev_info();
    create_action_info_error_info();
    create_action_info_ai_info();
    m_kia_main_window->create_action_graph_dock_widget(m_kia_menubar->get_menu_windows());
    m_kia_menubar->get_menu_commands()->addSeparator();
}

void KiaCore::correct_save_state_window(QDialog *window_info)
{
    connect(window_info, &QDialog::finished, this, [this, window_info](int result)
    {
        Q_UNUSED(result)
        if (m_kia_settings->m_kia_gui_settings->m_widget_is_closed && m_kia_settings->m_kia_gui_settings->m_widget_is_hide[window_info])
            m_kia_settings->m_kia_gui_settings->m_widget_is_hide[window_info] = true;
        else
            m_kia_settings->m_kia_gui_settings->m_widget_is_hide[window_info] = false;
    });
}

void KiaCore::create_kia_profile()
{
    m_kia_profile = new Kia_profile(m_kia_settings, m_kia_main_window);
    QString name_profile = "Основной";
    m_kia_profile->create_main_profile(name_profile);
    m_kia_menubar->get_menu_profile()->addAction("Основной", m_kia_menubar, [this]()
    {
        m_kia_settings->m_current_profile = 0;
        load_profile_settings();
    });
    connect(m_save_read_settings.get(), SIGNAL(send_to_kia_profile(QStringList)), m_kia_profile, SLOT(add_profile_slot(QStringList)));
    connect(m_kia_profile, &Kia_profile::create_action, this, [this](QString name_profile, int32_t num_profile)
    {
        m_profile_action.push_back(m_kia_menubar->get_menu_profile()->addAction(name_profile, m_kia_menubar, [this, num_profile]()
        {
            m_kia_settings->m_current_profile = num_profile;
            load_profile_settings();
        }));
    });
    connect(m_kia_profile, &Kia_profile::remove_action, this, [this](int32_t num_profile)
    {
        m_kia_menubar->get_menu_profile()->removeAction(m_profile_action[num_profile]);
        m_profile_action.erase(m_profile_action.begin() + num_profile);
    });
    m_save_read_settings->load_profile_settings();
}

void KiaCore::create_kia_options()
{

    create_kia_options_for_bi_command();

    create_kia_options_for_cyclogram();

    create_kia_options_for_command();

    create_kia_options_for_interface();
    m_kia_options = new Kia_options(m_kia_settings, m_kia_options_list, m_kia_main_window);
}


void KiaCore::set_kia_gui_settings_slot()
{
    m_kia_settings->m_kia_bokz_settings->m_count_bokz = m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi] * m_kia_settings->m_kia_bi_settings->m_count_bi;
    m_kia_settings->m_kia_data_to_server->m_is_used_bokz.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_settings->m_kia_data_to_server->m_td_change.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_settings->m_kia_data_to_server->m_address_change.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_settings->m_kia_data_to_server->m_mpi_num.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_settings->m_kia_data_to_server->m_lpi_change.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_settings->m_kia_data_to_server->m_mpi_num_index_of_num_bokz.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_settings->m_kia_data_to_server->m_address_change.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_settings->m_kia_data_to_server->m_num_used_bi.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_settings->m_kia_data_to_server->m_num_used_channel.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_window_info_mpi_for_dev.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_window_info_device_protocol.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_window_info_system_info.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_window_info_error_info.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_kia_window_info_ai_protocol.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);


    create_menubar();

    m_kia_main_window->show();

    create_kia_profile();

    create_window_is_work();


    m_kia_constructor.reset(new Kia_constructor(m_kia_settings, m_kia_main_window));
    m_kia_constructor->setWindowTitle("Коструктор");
    m_kia_constructor->set_type_dev(m_kia_settings->m_type_bokz, m_kia_settings->m_type_bi);
    create_kia_graph_manager();
    create_kia_table_manager();

    create_window_mpi();

    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        m_kia_window_info_mpi_for_dev[num_bokz] = new KiaWindowInfo(m_kia_main_window);
        m_kia_custom_dialog[WINDOW_MPI_DEV].push_back(new Kia_custom_dialog(m_kia_main_window));
        m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]->set_wiget_to_layout(m_kia_window_info_mpi_for_dev[num_bokz]);
        m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]->set_window_title("МКО прибора " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
                + " " + QString::number(num_bokz + 1));
        connect(m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz], &Kia_custom_dialog::set_new_parent, this, [this, num_bokz]()
        {
            m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]->hide();
            m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]->setParent(m_kia_main_window);
            m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]] = -1;
            m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]] = m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]->isVisible();
        });
        correct_save_state_window(m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]);

        //        m_keys_for_dock_widget["window_mko_dev_" + QString::number(num_bokz)].push_back(m_kia_main_window->set_to_dock_widget_window_info(m_kia_window_info_mpi_for_dev[num_bokz], "МКО прибора "
        //                                                                                                                                          + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
        //                                                                                        + " " + QString::number(num_bokz + 1)));

        m_kia_window_info_device_protocol[num_bokz] = new KiaWindowInfo(m_kia_main_window);
        m_kia_custom_dialog[WINDOW_DEV_PROTOCOL].push_back(new Kia_custom_dialog(m_kia_main_window));
        m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]->set_wiget_to_layout(m_kia_window_info_device_protocol[num_bokz]);
        m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]->set_window_title("Информация прибора "
                                                                             + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
                + " " + QString::number(num_bokz + 1));
        connect(m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz], &Kia_custom_dialog::set_new_parent, this, [this, num_bokz]()
        {
            m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]->hide();
            m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]->setParent(m_kia_main_window);
            m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]] = -1;
            m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]] = m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]->isVisible();
        });
        correct_save_state_window(m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]);
        //        m_keys_for_dock_widget["window_info_dev_" + QString::number(num_bokz)].push_back(m_kia_main_window->set_to_dock_widget_window_info(m_kia_window_info_device_protocol[num_bokz], "Информация прибора "
        //                                                                                                                                           + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
        //                                                                                         + " " + QString::number(num_bokz + 1)));

        m_kia_window_info_system_info[num_bokz] = new KiaWindowInfo(m_kia_main_window);
        m_kia_custom_dialog[WINDOW_SYSTEM_INFO].push_back(new Kia_custom_dialog(m_kia_main_window));
        m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]->set_wiget_to_layout(m_kia_window_info_system_info[num_bokz]);
        m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]->set_window_title("Системная информация "
                                                                            + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
                + " " + QString::number(num_bokz + 1));
        connect(m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz], &Kia_custom_dialog::set_new_parent, this, [this, num_bokz]()
        {
            m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]->hide();
            m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]->setParent(m_kia_main_window);
            m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]] = -1;
            m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]] = m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]->isVisible();
        });
        correct_save_state_window(m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]);
        //        m_keys_for_dock_widget["window_system_info_" + QString::number(num_bokz)].push_back(m_kia_main_window->set_to_dock_widget_window_info(m_kia_window_info_system_info[num_bokz], "Системная информация "
        //                                                                                                                                              + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
        //                                                                                            + " " + QString::number(num_bokz + 1)));

        m_kia_window_info_error_info[num_bokz] = new KiaWindowInfo(m_kia_main_window);
        m_kia_custom_dialog[WINDOW_ERROR_INFO].push_back(new Kia_custom_dialog(m_kia_main_window));
        m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]->set_wiget_to_layout(m_kia_window_info_error_info[num_bokz]);
        m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]->set_window_title("Ошибочная информация "
                                                                           + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
                + " " + QString::number(num_bokz + 1));
        connect(m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz], &Kia_custom_dialog::set_new_parent, this, [this, num_bokz]()
        {
            m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]->hide();
            m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]->setParent(m_kia_main_window);
            m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]] = -1;
            m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]] = m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]->isVisible();
        });
        correct_save_state_window(m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]);
        //        m_keys_for_dock_widget["window_error_info_" + QString::number(num_bokz)].push_back(m_kia_main_window->set_to_dock_widget_window_info(m_kia_window_info_error_info[num_bokz], "Ошибочная информация "
        //                                                                                                                                             + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
        //                                                                                           + " " + QString::number(num_bokz + 1)));

        m_kia_window_info_ai_protocol[num_bokz] = new KiaWindowInfo(m_kia_main_window);
        m_kia_custom_dialog[WINDOW_AI_PROTOCOL].push_back(new Kia_custom_dialog(m_kia_main_window));
        m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]->set_wiget_to_layout(m_kia_window_info_ai_protocol[num_bokz]);
        m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]->set_window_title("Автономные испытания "
                                                                            + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
                + " " + QString::number(num_bokz + 1));
        connect(m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz], &Kia_custom_dialog::set_new_parent, this, [this, num_bokz]()
        {
            m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]->hide();
            m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]->setParent(m_kia_main_window);
            m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]] = -1;
            m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]] = m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]->isVisible();
        });
        correct_save_state_window(m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]);



    }
    m_kia_window_info_mpi_command.resize(m_kia_settings->m_kia_bokz_settings->m_max_mpi_command);
    for (uint16_t num_mpi_command = 0; num_mpi_command < m_kia_settings->m_kia_bokz_settings->m_max_mpi_command; ++num_mpi_command)
    {
        m_kia_window_info_mpi_command[num_mpi_command].resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
        {
            m_kia_window_info_mpi_command[num_mpi_command][num_bokz] = new KiaWindowInfo(m_kia_main_window);
            m_kia_custom_dialog[WINDOW_MPI_COMMAND].push_back(new Kia_custom_dialog(m_kia_main_window));
            m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]->set_wiget_to_layout(m_kia_window_info_mpi_command[num_mpi_command][num_bokz]);
            m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]->set_window_title(m_kia_settings->m_kia_gui_settings->m_mpi_command_name[num_mpi_command].first
                                                                                                                                                        + " " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
                    + " " + QString::number(num_bokz + 1));
            connect(m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)], &Kia_custom_dialog::set_new_parent, this, [this, num_mpi_command, num_bokz]()
            {
                m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]->hide();
                m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]->setParent(m_kia_main_window);
                m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]] = -1;
                m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]] =
                        m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]->isVisible();
            });
            correct_save_state_window(m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]);
        }
    }

    create_window_state(m_kia_settings->m_type_bi);
    create_window_settings(m_kia_settings->m_type_bokz);

    create_kia_debug_commands();

    create_menu_action();

    create_kia_options();

}

void KiaCore::create_kia_options_for_bi_command()
{
    m_kia_options_bi = new Kia_options_bi(m_kia_settings, m_client, m_kia_main_window);
    auto pair = std::make_pair(m_kia_options_bi, "БИ");
    m_kia_options_list.push_back(pair);
}

void KiaCore::create_kia_options_for_cyclogram()
{
    m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram.resize(m_kia_settings->m_kia_bokz_settings->m_max_mpi_command);
    std::fill(m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram.begin(),
              m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram.end(), KiaS_FAIL);
    m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp.resize(m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp);
    std::fill(m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp.begin(),
              m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp.end(), KiaS_FAIL);
    m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai.resize(m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_ai);
    std::fill(m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai.begin(),
              m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai.end(), KiaS_FAIL);
    m_kia_options_cyclograms = new Kia_options_cyclograms(m_kia_settings, m_client, m_kia_main_window);
    auto pair = std::make_pair(m_kia_options_cyclograms, "Циклограммы");
    m_kia_options_list.push_back(pair);

    connect(m_save_read_settings.get(), SIGNAL(send_to_kia_options(qint16, QStringList)),
            m_kia_options_cyclograms, SLOT(set_load_settings(qint16, QStringList)));

    connect(m_save_read_settings.get(), SIGNAL(send_to_tp_cyclogram_settings(qint16, QStringList)),
            m_kia_options_cyclograms, SLOT(set_load_tp_settings(qint16, QStringList)));

    connect(m_save_read_settings.get(), SIGNAL(send_to_ri_cyclograms(qint16, QStringList)),
            m_kia_options_cyclograms, SLOT(load_for_specific_cyclogram(qint16, QStringList)));

    connect(m_save_read_settings.get(), SIGNAL(send_to_regular_cyclogram_do_command(qint16, qint16, QStringList)),
            m_kia_options_cyclograms, SLOT(set_load_regular_settings_do_command(qint16, qint16, QStringList)));

    connect(m_save_read_settings.get(), SIGNAL(send_frames_cyclograms(qint16, qint16)),
            m_kia_options_cyclograms, SLOT(load_for_cyclogram_do_frames(qint16, qint16)));

    connect(m_save_read_settings.get(), SIGNAL(send_to_power_cyclogram_do_command(qint16, qint16, QStringList)),
            m_kia_options_cyclograms, SLOT(set_load_power_settings_do_command(qint16, qint16, QStringList)));

}

void KiaCore::create_kia_options_for_command()
{
    m_kia_options_command = new Kia_options_command(m_kia_settings, m_client, m_kia_main_window);
    auto pair = std::make_pair(m_kia_options_command, "Команды");
    m_kia_options_list.push_back(pair);
    connect(m_client.get(), &Client::set_read_command, m_kia_options_command, &Kia_options_command::set_read_command);
}

void KiaCore::create_kia_options_for_interface()
{
    m_kia_options_interface = new Kia_options_interface(m_kia_settings, m_client, m_kia_main_window);
    auto pair = std::make_pair(m_kia_options_interface, "Интерфейс");
    m_kia_options_list.push_back(pair);
    QStringList list_name_table;
    QVector<QStringList> list_rows;
    list_name_table.push_back(m_kia_window_state_for_all_dev->windowTitle());
    list_rows.push_back(m_kia_window_state_for_all_dev->get_row());
    connect(m_kia_options_interface, &Kia_options_interface::send_state_and_num_row, this, [this](qint16 num_table, qint16 num_row, bool is_active)
    {
        Q_UNUSED(num_table)
        m_kia_window_state_for_all_dev->hide_or_show_row(num_row, is_active);
    });
    connect(m_kia_options_interface, &Kia_options_interface::send_color_and_num_row, this, [this](qint16 num_table, qint16 num_row, bool is_active)
    {
        Q_UNUSED(num_table)
        m_kia_window_state_for_all_dev->set_color_row(num_row, is_active);
    });
    m_kia_options_interface->create_window_state_settings(list_name_table, list_rows);

    m_kia_options_interface->create_actions_menu_settings(m_kia_menubar->get_menu_actions());

    connect(m_kia_options_interface, &Kia_options_interface::send_num_actions, this, [this](qint16 type_actions, qint16 num_actions, bool is_active)
    {
        m_kia_menubar->hide_or_show_actions(type_actions, num_actions, is_active);
    });

    m_kia_options_interface->create_menu_for_menu_bar(m_kia_menubar->get_menu_from_menubar());
    connect(m_kia_options_interface, &Kia_options_interface::send_num_menus, this, [this](qint16 type_menu, bool is_active)
    {
        m_kia_menubar->hide_or_show_menu(type_menu, is_active);
    });

    connect(m_save_read_settings.get(), SIGNAL(send_list_for_check_box_table_state(qint16, QStringList)),
            m_kia_options_interface, SLOT(set_check_box_for_table_state(qint16, QStringList)));
    connect(m_save_read_settings.get(), SIGNAL(send_list_for_check_box_color_table_state(qint16, QStringList)),
            m_kia_options_interface, SLOT(set_check_box_for_table_state_color(qint16, QStringList)));

    connect(m_save_read_settings.get(), SIGNAL(send_list_for_menu_actions(qint16, QStringList)),
            m_kia_options_interface, SLOT(set_list_for_menu_actions(qint16, QStringList)));

    connect(m_save_read_settings.get(), SIGNAL(send_to_list_for_check_box_menu_for_menubar(QStringList)),
            m_kia_options_interface, SLOT(set_list_for_menu_actions_for_menubar(QStringList)));
}

void KiaCore::create_kia_debug_commands()
{
    m_kia_debug_commands = new Kia_debug_commands(m_kia_settings, m_client, m_kia_main_window);
    m_kia_debug_commands->setWindowTitle("Отладочные команды");
    connect(m_kia_menubar, &KiaMenuBar::show_kia_debug_command, this, [this]()
    {
        m_kia_debug_commands->show();
    });
}

void KiaCore::create_kia_graph_manager()
{
    auto parent = m_kia_main_window->get_central_dock_widget();
    m_kia_graph_manager.reset(new Kia_graph_manager(m_kia_settings, m_kia_constructor, parent, m_kia_main_window));
    m_kia_menubar->get_menu_plots()->addAction("Добавить график", m_kia_menubar, [this]()
    {
        m_kia_constructor->show();
        m_kia_constructor->set_active(0);
    });
    m_kia_menubar->get_menu_plots()->addSeparator();
    connect(m_save_read_settings.get(), SIGNAL(send_to_plot_contructor(QStringList)), m_kia_graph_manager.get(), SLOT(create_plot_slot(QStringList)));
    connect(m_kia_graph_manager.get(), SIGNAL(create_action(QString, int32_t)), this, SLOT(create_action_for_graph(QString, int32_t)));
    connect(m_kia_graph_manager.get(), SIGNAL(remove_action(int32_t)), this, SLOT(remove_action_from_graph(int32_t)));

    auto graph_main_widget = m_kia_graph_manager->get_main_graph_widget();
    m_kia_main_window->set_widget_on_bottom(graph_main_widget);


}

void KiaCore::create_action_for_graph(QString name_graph, int32_t num_graph)
{
    auto graph_widget = m_kia_graph_manager->get_graph_widget(num_graph);
    connect(graph_widget, &Kia_custom_dialog::set_new_parent, this, [this, graph_widget]()
    {
        graph_widget->hide();
        graph_widget->setParent(m_kia_main_window);
        m_kia_settings->m_kia_gui_settings->m_current_num_parent[graph_widget] = -1;
        m_kia_settings->m_kia_gui_settings->m_widget_is_hide[graph_widget] = graph_widget->isVisible();
    });
    m_plot_action.push_back(m_kia_menubar->get_menu_plots()->addAction(name_graph, m_kia_menubar, [this, num_graph]()
    {

        m_kia_graph_manager->show_graphs(num_graph);

    }));
}

void KiaCore::remove_action_from_graph(int32_t num_graph)
{
    m_kia_menubar->get_menu_plots()->removeAction(m_plot_action[num_graph]);
    m_plot_action.erase(m_plot_action.begin() + num_graph);
}

void KiaCore::create_kia_table_manager()
{
    auto parent = m_kia_main_window->get_central_dock_widget();
    m_kia_table_manager.reset(new Kia_table_manager(m_kia_settings, m_kia_constructor, parent, m_kia_main_window));
    m_kia_menubar->get_menu_tables()->addAction("Добавить таблицу", m_kia_menubar, [this]()
    {
        m_kia_constructor->show();
        m_kia_constructor->set_active(1);
    });
    m_kia_menubar->get_menu_tables()->addSeparator();
    connect(m_save_read_settings.get(), SIGNAL(send_to_table_constructor(QStringList, QStringList)), m_kia_table_manager.get(), SLOT(create_table_slot(QStringList, QStringList)));
    connect(m_kia_table_manager.get(), SIGNAL(create_action(QString, int32_t)), this, SLOT(create_action_for_table(QString, int32_t)));
    connect(m_kia_table_manager.get(), SIGNAL(remove_action(int32_t)), this, SLOT(remove_action_from_table(int32_t)));
    auto table_widget_list = m_kia_table_manager->get_table_widgets();
    for (uint16_t num_widget = 0; num_widget < table_widget_list.size(); ++num_widget)
    {
        correct_save_state_window(table_widget_list[num_widget]);
    }
}

void KiaCore::create_action_for_table(QString name_graph, int32_t num_table)
{
    auto table_widget = m_kia_table_manager->get_table_widget(num_table);
    connect(table_widget, &Kia_custom_dialog::set_new_parent, this, [this, table_widget]()
    {
        table_widget->hide();
        table_widget->setParent(m_kia_main_window);
        m_kia_settings->m_kia_gui_settings->m_current_num_parent[table_widget] = -1;
        m_kia_settings->m_kia_gui_settings->m_widget_is_hide[table_widget] = table_widget->isVisible();
    });
    m_table_action.push_back(m_kia_menubar->get_menu_tables()->addAction(name_graph, m_kia_menubar, [this, num_table]()
    {
        m_kia_table_manager->show_tables(num_table);
    }));
}

void KiaCore::remove_action_from_table(int32_t num_graph)
{
    m_kia_menubar->get_menu_tables()->removeAction(m_table_action[num_graph]);
    m_table_action.erase(m_table_action.begin() + num_graph);
}

void KiaCore::create_window_mpi()
{
    m_kia_window_info_mpi = new KiaWindowInfo(m_kia_main_window);
    m_kia_custom_dialog[WINDOW_MPI].push_back(new Kia_custom_dialog(m_kia_main_window));
    m_kia_custom_dialog[WINDOW_MPI][0]->set_wiget_to_layout(m_kia_window_info_mpi);
    m_kia_custom_dialog[WINDOW_MPI][0]->set_window_title("МКО " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]);
    connect(m_kia_custom_dialog[WINDOW_MPI][0], &Kia_custom_dialog::set_new_parent, this, [this]()
    {
        m_kia_custom_dialog[WINDOW_MPI][0]->hide();
        m_kia_custom_dialog[WINDOW_MPI][0]->setParent(m_kia_main_window);
        m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_MPI][0]] = -1;
        m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_MPI][0]] = m_kia_custom_dialog[WINDOW_MPI][0]->isVisible();
    });
    correct_save_state_window(m_kia_custom_dialog[WINDOW_MPI][WINDOW_MPI]);
}


void KiaCore::create_window_state(qint16 type_bi)
{
    m_kia_window_state_for_all_dev = new KiaWindowState(m_kia_settings, m_kia_main_window);
    m_kia_window_state_for_all_dev->setWindowTitle("Окно состояний");
    m_keys_for_dock_widget["window_state"].push_back(m_kia_main_window->set_to_dock_widget_status_info(m_kia_window_state_for_all_dev, "Окно состояний"));
    m_kia_window_state_for_all_dev->show();
    m_kia_window_state_for_all_dev->table_setup(type_bi);
    connect(m_client.get(), SIGNAL(send_to_table_state_window(qint16, QStringList)), this, SLOT(set_data_to_table_state(qint16, QStringList)));
    connect(m_client.get(), SIGNAL(set_1s_mark_status(qint16)), this, SLOT(set_status_bi_1s_mark(qint16)));
}

void KiaCore::create_window_settings(qint16 type_bokz)
{
    m_kia_settings->m_kia_bokz_settings->m_bokz_row_name[type_bokz] << "Используется" << "Адрес МПИ" << "МПИ" << "ЛПИ" << "БИ"
                                                                    << "Номер канала" << "Группа ТД";
    m_kia_window_settings_for_all_dev = new KiaWindowSettings(m_kia_settings, m_kia_main_window);
    m_kia_window_settings_for_all_dev->setWindowTitle("Окно параметров прибора");
    m_kia_window_settings_for_all_dev->show();
    m_keys_for_dock_widget["window_param_dev"].push_back(m_kia_main_window->set_to_dock_widget_status_info(m_kia_window_settings_for_all_dev, "Окно параметров прибора"));

    connect(m_kia_window_settings_for_all_dev, SIGNAL(send_value_width_for_state_table(qint16, qint16)), m_kia_window_state_for_all_dev, SLOT(set_width_for_vertical_header(qint16, qint16)));

    connect(m_kia_window_settings_for_all_dev, SIGNAL(send_value_width_for_state_table(qint16, qint16)), m_kia_window_is_work, SLOT(set_width_for_vertical_header(qint16, qint16)));

    m_kia_window_settings_for_all_dev->create_table_settings(type_bokz);
    connect(m_client.get(), SIGNAL(send_to_table_settings_window(QStringList)), m_kia_window_settings_for_all_dev, SLOT(set_data_table_settings(QStringList)));
    connect(m_kia_window_settings_for_all_dev, SIGNAL(send_data_from_client(qint16, QStringList)), this, SLOT(send_data_from_client(qint16, QStringList)));
    connect(m_save_read_settings.get(), SIGNAL(send_to_table_settings_window(QStringList)), m_kia_window_settings_for_all_dev, SLOT(set_data_table_settings(QStringList)));
}

void KiaCore::create_action_info_ai_info()
{
    m_kia_menubar->get_menu_windows()->addAction("Окно Автономных испытаний", m_kia_menubar, [this]()
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
        {
            if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
            {
                m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget]);
                m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]->show();
                m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]] = m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget;
                m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]] = m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]->isVisible();
            }
        }
    });
    connect(m_client.get(), SIGNAL(set_window_info_ai_window(qint16, QString)), this, SLOT(set_window_info_ai_window(qint16, QString)));
}

void KiaCore::create_action_info_system_info()
{
    m_kia_menubar->get_menu_windows()->addAction("Окно Системная информация", m_kia_menubar, [this]()
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
        {
            if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
            {
                m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget]);
                m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]->show();
                m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]] = m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget;
                m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]] = m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]->isVisible();
            }
        }
    });
    connect(m_client.get(), SIGNAL(set_window_info_system_window(qint16, QString)), this, SLOT(set_window_info_system_window(qint16, QString)));
}

void KiaCore::create_action_info_error_info()
{
    m_kia_menubar->get_menu_windows()->addAction("Окно Ошибочная информация", m_kia_menubar, [this]()
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
        {
            if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
            {
                m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget]);
                m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]->show();
                m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]] = m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget;
                m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]] = m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]->isVisible();
            }
        }
    });
    connect(m_client.get(), SIGNAL(set_window_info_error_window(qint16, QString)), this, SLOT(set_window_info_error_window(qint16, QString)));
}

void KiaCore::create_action_info_dev()
{
    m_kia_menubar->get_menu_windows()->addAction("Окно Информация приборов", m_kia_menubar, [this]()
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_data_to_server->m_is_used_bokz.size(); ++num_bokz)
        {
            if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
            {
                m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget]);
                m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]->show();
                m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]] = m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget;
                m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]] = m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]->isVisible();
                //                for (auto& num_window : m_keys_for_dock_widget["window_info_dev_" + QString::number(num_bokz)])
                //                    m_kia_settings->m_kia_gui_settings->m_dock_widget[num_window]->toggleView();
            }
        }
    });
    connect(m_client.get(), SIGNAL(set_window_info_device_protocol(qint16, qint16, QString)), this, SLOT(set_window_info_device_protocol(qint16, qint16, QString)));
}

void KiaCore::create_window_is_work()
{
    m_kia_window_is_work = new KiaWindowIsWork(m_kia_settings, m_client, m_kia_main_window);
    connect(m_client.get(), SIGNAL(check_connect(qint16, qint16)), m_kia_window_is_work, SLOT(check_connect(qint16, qint16)));
    m_kia_window_is_work->setWindowTitle("Статус работы");
    connect(m_kia_window_is_work, SIGNAL(set_stop(qint16)), this, SLOT(set_otclp_stop(qint16)));
    m_keys_for_dock_widget["window_state_work"].push_back(m_kia_main_window->set_to_dock_widget_status_info(m_kia_window_is_work, "Статус работы"));
    m_kia_window_is_work->show();
    m_kia_window_is_work->create_status_bi();
    m_kia_settings->m_kia_bokz_settings->m_bokz_status_row_name[m_kia_settings->m_type_bokz]  << "БШВ" << "КС 1" << "КС 2";
    m_kia_window_is_work->create_table_status_bokz();
    connect(m_client.get(), SIGNAL(send_status_info(QStringList)), m_kia_window_is_work, SLOT(set_data_to_table(QStringList)));
    connect(m_kia_main_window, SIGNAL(set_stop()), m_kia_window_is_work, SLOT(set_stop_slot()));

}

void KiaCore::create_mpi_command_action()
{
    for (uint16_t num_mpi_command = 0; num_mpi_command < m_kia_settings->m_kia_bokz_settings->m_max_mpi_command; ++num_mpi_command)
    {
        m_kia_menubar->get_menu_windows()->addAction("Окно " + m_kia_settings->m_kia_gui_settings->m_mpi_command_name[num_mpi_command].first, m_kia_menubar, [this, num_mpi_command]()
        {
            for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
            {
                if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
                {
                    m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget]);
                    m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]->show();
                    m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]] = m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget;
                    m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]] =
                            m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]->isVisible();
                    //                    for (auto& num_window : m_keys_for_dock_widget["window_mpi_command_" + QString::number(num_mpi_command) + "_" + QString::number(num_bokz)])
                    //                        m_kia_settings->m_kia_gui_settings->m_dock_widget[num_window]->toggleView();
                }
            }
        });
    }
}

void KiaCore::create_action_info_mpi_info()
{

    m_kia_menubar->get_menu_windows()->addAction("Окно МКО", m_kia_menubar, [this]()
    {
        m_kia_custom_dialog[WINDOW_MPI][0]->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget]);
        m_kia_custom_dialog[WINDOW_MPI][0]->show();
        m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_MPI][0]] = m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget;
        m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_MPI][0]] = m_kia_custom_dialog[WINDOW_MPI][0]->isVisible();
    });
    //set_dock_actions(std::make_pair("window_mko", action_mpi));
    connect(m_client.get(), SIGNAL(set_window_info_mpi(qint16, QString)), this, SLOT(set_window_info_mpi(qint16, QString)));
}

void KiaCore::create_action_info_mpi_dev_info()
{
    m_kia_menubar->get_menu_windows()->addAction("Окно МКО приборов", m_kia_menubar, [this]()
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_data_to_server->m_is_used_bokz.size(); ++num_bokz)
        {
            if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
            {
                m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget]);
                m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]->show();
                m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]] = m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget;
                m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]] = m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]->isVisible();
            }
        }
    });
}

void KiaCore::set_data_to_table_state(qint16 type_bi, QStringList data_from_server)
{
    m_kia_window_state_for_all_dev->set_data_to_table_state(type_bi, data_from_server);
}

void KiaCore::set_status_bi_1s_mark(qint16 num_bi)
{
    m_kia_window_state_for_all_dev->set_status_bi_1s_mark(num_bi);
}

void KiaCore::send_data_from_client(qint16 num, QStringList data_for_server)
{
    m_client->send_data_to_server(num, data_for_server);
}

void KiaCore::set_window_info_mpi(qint16 type_mpi_dev, QString data_from_server)
{
    m_kia_window_info_mpi->append_info_to_window(data_from_server);
    m_kia_window_info_mpi_for_dev[type_mpi_dev]->append_info_to_window(data_from_server);
}

void KiaCore::set_window_info_system_window(qint16 num_bokz, QString data_from_server)
{
    m_kia_window_info_system_info[num_bokz]->append_info_to_window(data_from_server);
}

void KiaCore::set_window_info_ai_window(qint16 num_bokz, QString data_from_server)
{
    m_kia_window_info_ai_protocol[num_bokz]->append_info_to_window(data_from_server);
}

void KiaCore::set_window_info_error_window(qint16 num_bokz, QString data_from_server)
{
    m_kia_window_info_error_info[num_bokz]->set_info_to_window(data_from_server);
}

void KiaCore::set_window_info_device_protocol(qint16 num_mpi_command, qint16 num_bokz, QString data_from_server)
{
    m_kia_window_info_device_protocol[num_bokz]->append_info_to_window(data_from_server);
    if (num_mpi_command < m_kia_settings->m_kia_bokz_settings->m_max_mpi_command)
        m_kia_window_info_mpi_command[num_mpi_command][num_bokz]->set_info_to_window(data_from_server);

}

void KiaCore::set_otclp_stop(qint16 is_otclp)
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_STOP, data_for_server);
    if (is_otclp != 0)
    {
        m_client->send_data_to_server(COMMAND_OTCLP, data_for_server);
    }
}

void KiaCore::reset_before_load_profile()
{
    m_kia_main_window->remove_tab_settings();

    m_kia_constructor->remove_list();

}

void KiaCore::load_profile_settings()
{
    reset_before_load_profile();
    m_save_read_settings->load_pos_and_size_widgets("m_kia_main_window", m_kia_main_window);
    m_save_read_settings->load_settings();

    m_kia_menubar->load_mode_menu_bi();
    m_save_read_settings->load_pos_and_size_widgets("window_is_work", m_kia_window_is_work);

    m_save_read_settings->load_pos_and_size_widgets("table_state", m_kia_window_state_for_all_dev);

    m_save_read_settings->load_pos_and_size_widgets("table_settings", m_kia_window_settings_for_all_dev);
    m_save_read_settings->load_pos_and_size_widgets("kia_debug_commands", m_kia_debug_commands);

    m_save_read_settings->load_pos_and_size_widgets("m_kia_options", m_kia_options);

    m_save_read_settings->load_tabs_settings();

    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        m_save_read_settings->load_state_widgets("mpi_for_dev_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]);
        m_save_read_settings->load_state_widgets("device_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]);
        m_save_read_settings->load_state_widgets("system_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]);
        m_save_read_settings->load_state_widgets("error_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]);
        m_save_read_settings->load_state_widgets("ai_protocol_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]);

        m_save_read_settings->load_pos_and_size_widgets("mpi_for_dev_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_MPI_DEV][num_bokz]);
        m_save_read_settings->load_pos_and_size_widgets("device_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_DEV_PROTOCOL][num_bokz]);
        m_save_read_settings->load_pos_and_size_widgets("system_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_SYSTEM_INFO][num_bokz]);
        m_save_read_settings->load_pos_and_size_widgets("error_info_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_ERROR_INFO][num_bokz]);
        m_save_read_settings->load_pos_and_size_widgets("ai_protocol_" + QString::number(num_bokz), m_kia_custom_dialog[WINDOW_AI_PROTOCOL][num_bokz]);
    }

    m_save_read_settings->load_pos_and_size_widgets("mpi_all_dev", m_kia_custom_dialog[WINDOW_MPI][0]);
    m_save_read_settings->load_state_widgets("mpi_all_dev", m_kia_custom_dialog[WINDOW_MPI][0]);

    for (uint16_t num_mpi_command = 0; num_mpi_command < m_kia_settings->m_kia_bokz_settings->m_max_mpi_command; ++num_mpi_command)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
        {
            m_save_read_settings->load_state_widgets("mpi_command_wnd_" + QString::number(num_mpi_command) + "_" + QString::number(num_bokz),
                                                     m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]);
            m_save_read_settings->load_pos_and_size_widgets("mpi_command_wnd_" + QString::number(num_mpi_command) + "_" + QString::number(num_bokz),
                                                            m_kia_custom_dialog[WINDOW_MPI_COMMAND][num_bokz + (num_mpi_command * m_kia_settings->m_kia_bokz_settings->m_count_bokz)]);
        }
    }


    m_save_read_settings->load_graph_settings();

    auto graph_widget_list = m_kia_graph_manager->get_graph_widgets();
    for (uint16_t num_widget = 0; num_widget < graph_widget_list.size(); ++num_widget)
    {
        m_save_read_settings->load_state_widgets("graph_" + QString::number(num_widget), graph_widget_list[num_widget]);
        m_save_read_settings->load_pos_and_size_widgets("graph_" + QString::number(num_widget), graph_widget_list[num_widget]);
    }

    m_save_read_settings->load_table_settings();
    auto table_widget_list = m_kia_table_manager->get_table_widgets();
    for (uint16_t num_widget = 0; num_widget < table_widget_list.size(); ++num_widget)
    {
        m_save_read_settings->load_state_widgets("table_" + QString::number(num_widget), table_widget_list[num_widget]);
        m_save_read_settings->load_pos_and_size_widgets("table_" + QString::number(num_widget), table_widget_list[num_widget]);
    }

    m_save_read_settings->load_state_dock_manager(m_dock_manager);

}

void KiaCore::show_kia_profile_slot()
{
    m_kia_profile->show();
    m_kia_profile->setWindowTitle("Настройки профиля");
}

