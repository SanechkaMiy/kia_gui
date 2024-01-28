#include "kia_menu.h"

Kia_menu::Kia_menu(std::shared_ptr<Client> client, std::shared_ptr<Kia_settings> kia_settings) :
    m_client(client),
    m_kia_settings(kia_settings)
{
    map_key_command[SHTMI_1] = QKeySequence(Qt::Key_F2);
    map_key_command[SHTMI_2] = QKeySequence(Qt::Key_F3);
    map_key_command[MSHI_OR] = QKeySequence(Qt::Key_F4);
    map_key_command[DTMI_ONE] = QKeySequence(Qt::Key_F5);
    map_key_command[MLOCK_ONE] = QKeySequence(Qt::Key_F6);
    map_key_command[SMTI] = QKeySequence();
    map_key_command[VMTI] = QKeySequence();
    map_key_command[SYNCHRO] = QKeySequence(Qt::Key_F7);
    map_key_command[SKOR] = QKeySequence();
    map_key_command[COMMAND_NO] = QKeySequence();
    map_key_command[COMMAND_TO] = QKeySequence();
    map_key_command[COMMAND_LOC] = QKeySequence();
    map_key_command[COMMAND_OTCLP] = QKeySequence();
    map_key_command[COMMAND_OS] = QKeySequence();
    map_key_command[COMMAND_VSKOU] = QKeySequence();
    map_key_command[COMMAND_ZKR] = QKeySequence();
    map_key_command[COMMAND_FULL_EXP] = QKeySequence();

    map_key_cyclogram_tp[CYCLOGRAM_NO] = QKeySequence(Qt::CTRL + Qt::Key_N);
    map_key_cyclogram_tp[CYCLOGRAM_TO] = QKeySequence(Qt::CTRL + Qt::Key_T);
    map_key_cyclogram_tp[CYCLOGRAM_LOC] = QKeySequence(Qt::CTRL + Qt::Key_L);
    map_key_cyclogram_tp[CYCLOGRAM_OO] = QKeySequence(Qt::CTRL + Qt::Key_O);

    map_key_cyclogram_ai[CYCLOGRAM_STATE_ON] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_TEST_ADRESS] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_TEST_MKO] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_1S_MARK] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_OPERATION] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_SYNCHRO] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_STATE_OFF] = QKeySequence();

    map_key_cyclogram_ri[CYCLOGRAM_TECH_RUN] = QKeySequence();
    map_key_cyclogram_ri[CYCLOGRAM_ZKR] = QKeySequence();
    map_key_cyclogram_ri[CYCL_FULL_FRAMES] = QKeySequence();

    map_key_cyclogram_power[CYCLOGRAM_STATE_ON] = QKeySequence();
    map_key_cyclogram_power[CYCLOGRAM_STATE_OFF] = QKeySequence();
}

void Kia_menu::create_action_state_power(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> stated_work_action;
    for (auto el : m_kia_settings->m_kia_gui_settings->m_cyclogram_power_name)
    {
        stated_work_action.push_back(std::make_tuple(el.first, map_key_cyclogram_power[el.second], el.second));
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

void Kia_menu::create_action_state_work(QMenu *menu)
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

void Kia_menu::create_action_pci(QMenu *menu)
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

void Kia_menu::create_action_res(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> res_action;
    for (auto el : m_kia_settings->m_kia_gui_settings->m_cyclogram_ri_name)
    {
        res_action.push_back(std::make_tuple(el.first, map_key_cyclogram_ri[el.second], el.second));
    }
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

void Kia_menu::create_action_commands(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> commands_action;
    for (auto el : m_kia_settings->m_kia_gui_settings->m_mpi_command_name)
    {
        commands_action.push_back(std::make_tuple(el.first, map_key_command[el.second], el.second));
    }

    for (auto el : m_kia_settings->m_kia_gui_settings->m_mpi_other_command_name)
    {
        commands_action.push_back(std::make_tuple(el.first, map_key_command[el.second], el.second));
    }


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

void Kia_menu::create_action_get_frames(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> frames_action;
    frames_action.push_back(std::make_tuple("Полный кадр", QKeySequence(), DO_FULL_FRAME));
    frames_action.push_back(std::make_tuple("Бинированный кадр", QKeySequence(), DO_BIN_FRAME));
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
