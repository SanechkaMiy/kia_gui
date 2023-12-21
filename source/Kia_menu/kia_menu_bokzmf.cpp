#include "kia_menu_bokzmf.h"

Kia_menu_bokzmf::Kia_menu_bokzmf(std::shared_ptr<Client> client) :
    m_client(client)
{

}

void Kia_menu_bokzmf::create_action_state_work(QMenu *menu)
{

}

void Kia_menu_bokzmf::create_action_pci(QMenu *menu)
{

}

void Kia_menu_bokzmf::create_action_res(QMenu *menu)
{

}

void Kia_menu_bokzmf::create_action_commands(QMenu *menu)
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> commands_action;
    commands_action.push_back(std::make_tuple("ШТМИ1", QKeySequence(Qt::Key_F2), SHTMI_1));
    commands_action.push_back(std::make_tuple("ШТМИ2", QKeySequence(Qt::Key_F3), SHTMI_2));
    commands_action.push_back(std::make_tuple("МШИ ОР", QKeySequence(Qt::Key_F4), MSHI_OR));
    commands_action.push_back(std::make_tuple("ДТМИ", QKeySequence(Qt::Key_F5), DTMI_ONE));
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
