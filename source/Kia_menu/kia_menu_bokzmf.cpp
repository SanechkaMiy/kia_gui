#include "kia_menu_bokzmf.h"

Kia_menu_bokzmf::Kia_menu_bokzmf(std::shared_ptr<Client> client, std::shared_ptr<Kia_settings> kia_settings) :
    m_client(client),
    m_kia_settings(kia_settings)
{

}

void Kia_menu_bokzmf::create_action_state_work(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> stated_work_action;

    map_key_cyclogram_tp[CYCLOGRAM_NO] = QKeySequence(Qt::CTRL + Qt::Key_N);
    map_key_cyclogram_tp[CYCLOGRAM_TO] = QKeySequence(Qt::CTRL + Qt::Key_T);
    map_key_cyclogram_tp[CYCLOGRAM_LOC] = QKeySequence(Qt::CTRL + Qt::Key_L);
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

void Kia_menu_bokzmf::create_action_pci(QMenu *menu)
{
    menu->addAction("Тест проверки адресов", menu, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_TEST_ADRESS, data_for_server);
    });
    menu->addAction("Тест МПИ", menu, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_TEST_MKO, data_for_server);
    });
}

void Kia_menu_bokzmf::create_action_res(QMenu *menu)
{

}

void Kia_menu_bokzmf::create_action_commands(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> commands_action;

    for (auto el : m_kia_settings->m_kia_gui_settings->m_mpi_command_name)
    {
        commands_action.push_back(std::make_tuple(el.first, map_key_command[el.second], el.second));
    }
    commands_action.push_back(std::make_tuple("СМТИ", QKeySequence(), SMTI));
    commands_action.push_back(std::make_tuple("ВМТИ", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("separator", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("Команда БШВ", QKeySequence(Qt::Key_F7), COMMAND_BSHV));
    commands_action.push_back(std::make_tuple("Команда СКОР", QKeySequence(), SKOR));
    commands_action.push_back(std::make_tuple("Команда ОО", QKeySequence(), COMMAND_OO));
    commands_action.push_back(std::make_tuple("Команда ЛОК", QKeySequence(), COMMAND_LOC));
    commands_action.push_back(std::make_tuple("Команда РСТ", QKeySequence(), COMMAND_RESTART));
    commands_action.push_back(std::make_tuple("Команда ОТКЛ Р", QKeySequence(), COMMAND_OTCLP));
    commands_action.push_back(std::make_tuple("separator", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("Команда ОС", QKeySequence(), COMMAND_OS));
    commands_action.push_back(std::make_tuple("Команда ВСКОУ", QKeySequence(), COMMAND_VSKOU));
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

void Kia_menu_bokzmf::create_action_get_frames(QMenu *menu)
{

}
