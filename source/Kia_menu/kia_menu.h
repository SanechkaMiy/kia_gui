#ifndef KIA_MENU_H
#define KIA_MENU_H
#include "client.h"
#include "Kia_main_struct.h"
#include <QMenu>
class Kia_menu
{
public:
    Kia_menu(std::shared_ptr<Client> client, std::shared_ptr<Kia_settings> kia_settings);
    void create_action_state_power(QMenu* menu);
    void create_action_state_work(QMenu* menu);
    void create_action_pci(QMenu* menu);
    void create_action_res(QMenu* menu);
    void create_action_commands(QMenu* menu);
    void create_action_get_frames(QMenu* menu);
private:
    std::shared_ptr<Client> m_client;
    std::shared_ptr<Kia_settings> m_kia_settings;
    enum st_work_action
    {
        NAME_ACTION = 0,
        HOT_KEY = 1,
        NUM_COMMAND = 2,
    };
    QMap<uint16_t, QKeySequence> map_key_command;
    QMap<uint16_t, QKeySequence> map_key_cyclogram_tp;
    QMap<uint16_t, QKeySequence> map_key_cyclogram_ai;
    QMap<uint16_t, QKeySequence> map_key_cyclogram_ri;
    QMap<uint16_t, QKeySequence> map_key_cyclogram_power;
};

#endif // KIA_MENU_H
