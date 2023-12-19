#include "kia_menu_bokzm60.h"

Kia_menu_bokzm60::Kia_menu_bokzm60(std::shared_ptr<Client> client) :
    m_client(client)
{

}

void Kia_menu_bokzm60::create_action_state_work(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> stated_work_action;
    stated_work_action.push_back(std::make_tuple("Начальная ориентация (НО)", QKeySequence(Qt::CTRL + Qt::Key_N), CYCLOGRAM_NO));
    stated_work_action.push_back(std::make_tuple("Текущая ориентация (ТО)", QKeySequence(Qt::CTRL + Qt::Key_T), CYCLOGRAM_TO));
    stated_work_action.push_back(std::make_tuple("Локализация (ЛОК)", QKeySequence(Qt::CTRL + Qt::Key_L), CYCLOGRAM_LOC));
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
    menu->addAction("Тест участка включения", menu, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_STATE_ON, data_for_server);
    });
    menu->addSeparator();
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
    menu->addAction("Тест 1с метки", menu, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_1S_MARK, data_for_server);
    });
    menu->addAction("Тест функционирования", menu, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_OPERATION, data_for_server);
    });
    menu->addAction("Тест Синхро", menu, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_SYNCHRO, data_for_server);
    });
    menu->addSeparator();
    menu->addAction("Тест участка выключения", menu, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_STATE_OFF, data_for_server);
    });

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
    commands_action.push_back(std::make_tuple("ШТМИ1", QKeySequence(Qt::Key_F2), SHTMI_1));
    commands_action.push_back(std::make_tuple("ШТМИ2", QKeySequence(Qt::Key_F3), SHTMI_2));
    commands_action.push_back(std::make_tuple("МШИ ОР", QKeySequence(Qt::Key_F4), MSHI_OR));
    commands_action.push_back(std::make_tuple("ДТМИ", QKeySequence(Qt::Key_F5), DTMI_ONE));
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
