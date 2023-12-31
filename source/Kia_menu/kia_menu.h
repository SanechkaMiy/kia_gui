#ifndef KIA_MENU_H
#define KIA_MENU_H
#include <QMenu>
#include "client.h"

class Kia_menu
{
public:
    Kia_menu();
    enum st_work_action
    {
        NAME_ACTION = 0,
        HOT_KEY = 1,
        NUM_COMMAND = 2,
    };
    QMap<uint16_t, QKeySequence> map_key_command;
    QMap<uint16_t, QKeySequence> map_key_cyclogram_tp;
    QMap<uint16_t, QKeySequence> map_key_cyclogram_ai;
    virtual void create_action_state_work(QMenu* menu) = 0;
    virtual void create_action_pci(QMenu* menu) = 0;
    virtual void create_action_res(QMenu* menu) = 0;
    virtual void create_action_commands(QMenu* menu) = 0;
    virtual void create_action_get_frames(QMenu* menu) = 0;
    virtual ~Kia_menu() = default;
};

#endif // KIA_MENU_H
