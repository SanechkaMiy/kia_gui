#include "kia_menu_bokzm60.h"

Kia_menu_bokzm60::Kia_menu_bokzm60(std::shared_ptr<Client> client, std::shared_ptr<Kia_settings> kia_settings) :
    m_client(client),
    m_kia_settings(kia_settings)
{

}

void Kia_menu_bokzm60::create_action_state_work(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> stated_work_action;
    for (auto el : m_kia_settings->m_kia_gui_settings->m_cyclogram_tp_name)
    {
        stated_work_action.push_back(std::make_tuple(el.first, map_key_cyclogram_tp[el.second], el.second));
    }
    for (auto& el : stated_work_action)
    {
        auto action = menu->addAction(std::get<NAME_ACTION>(el), menu, [this, el]()
        {
            QStringList data_for_server;
            m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
        });
        action->setShortcut(std::get<HOT_KEY>(el));
    }
}

void Kia_menu_bokzm60::create_action_pci(QMenu *menu)
{

    std::vector<std::tuple<QString, QKeySequence, uint16_t>> cyclograms_ai;
    for (auto el : m_kia_settings->m_kia_gui_settings->m_cyclogram_ai_name)
    {

        cyclograms_ai.push_back(std::make_tuple(el.first, map_key_cyclogram_ai[el.second], el.second));

    }

    for (auto& el : cyclograms_ai)
    {
        if (std::get<NUM_COMMAND>(el) == CYCLOGRAM_STATE_OFF)
            menu->addSeparator();

        auto action = menu->addAction(std::get<NAME_ACTION>(el), menu, [this, el]()
        {
            QStringList data_for_server;
            m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
        });

        action->setShortcut(std::get<HOT_KEY>(el));

        if (std::get<NUM_COMMAND>(el) == CYCLOGRAM_STATE_ON)
            menu->addSeparator();


    }

}

void Kia_menu_bokzm60::create_action_res(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> res_action;
    res_action.push_back(std::make_tuple("Испытание крышки", QKeySequence(), CYCLOGRAM_ZKR));
    res_action.push_back(std::make_tuple("Технологический прогон", QKeySequence(), CYCLOGRAM_TECH_RUN));
    res_action.push_back(std::make_tuple("Получение темновых кадров", QKeySequence(), CYCL_FULL_FRAMES));
    for (auto& el : res_action)
    {
        auto action = menu->addAction(std::get<NAME_ACTION>(el), menu, [this, el]()
        {
            QStringList data_for_server;
            m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
        });
        action->setShortcut(std::get<HOT_KEY>(el));
    }
}

void Kia_menu_bokzm60::create_action_commands(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> commands_action;
    for (auto el : m_kia_settings->m_kia_gui_settings->m_mpi_command_name)
    {
        commands_action.push_back(std::make_tuple(el.first, map_key_command[el.second], el.second));
    }
    commands_action.push_back(std::make_tuple("СМТИ", QKeySequence(), SMTI));
    commands_action.push_back(std::make_tuple("ВМТИ", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("separator", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("Команда СИНХРО", QKeySequence(Qt::Key_F7), SYNCHRO));
    commands_action.push_back(std::make_tuple("Команда СКОР", QKeySequence(), SKOR));
    commands_action.push_back(std::make_tuple("Команда НО", QKeySequence(), COMMAND_NO));
    commands_action.push_back(std::make_tuple("Команда ТО", QKeySequence(), COMMAND_TO));
    commands_action.push_back(std::make_tuple("Команда ЛОК", QKeySequence(), COMMAND_LOC));
    commands_action.push_back(std::make_tuple("Команда ОТКЛ Р", QKeySequence(), COMMAND_OTCLP));
    commands_action.push_back(std::make_tuple("separator", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("Команда ОС", QKeySequence(), COMMAND_OS));
    commands_action.push_back(std::make_tuple("Команда ВСКОУ", QKeySequence(), COMMAND_VSKOU));
    commands_action.push_back(std::make_tuple("Команда ЗКР", QKeySequence(), COMMAND_ZKR));
    commands_action.push_back(std::make_tuple("separator", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("Полная экспозиция", QKeySequence(), COMMAND_FULL_EXP));
    commands_action.push_back(std::make_tuple("separator", QKeySequence(), VMTI));
    for (auto& el : commands_action)
    {
        if (std::get<NAME_ACTION>(el) == "separator")
        {
            menu->addSeparator();
        }
        else
        {
            auto action = menu->addAction(std::get<NAME_ACTION>(el), menu, [this, el]()
            {
                QStringList data_for_server;
                m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
            });
            action->setShortcut(std::get<HOT_KEY>(el));
        }
    }
}

void Kia_menu_bokzm60::create_action_get_frames(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> frames_action;
    frames_action.push_back(std::make_tuple("Полный кадр", QKeySequence(), DO_FULL_FRAME));
    frames_action.push_back(std::make_tuple("Бинированный кадр", QKeySequence(), DO_FULL_FRAME));
    for (auto& el : frames_action)
    {
        auto action = menu->addAction(std::get<NAME_ACTION>(el), menu, [this, el]()
        {
            QStringList data_for_server;
            m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
        });
        action->setShortcut(std::get<HOT_KEY>(el));
    }
}
