#ifndef KIA_MENU_H
#define KIA_MENU_H
#include <QMenu>
#include "client.h"

class Kia_menu
{
public:
    virtual void create_action_state_work(QMenu* menu) = 0;
    virtual void create_action_pci(QMenu* menu) = 0;
    virtual void create_action_res(QMenu* menu) = 0;
    virtual void create_action_commands(QMenu* menu) = 0;
    virtual void create_action_get_frames(QMenu* menu) = 0;
    virtual ~Kia_menu() = default;
};

#endif // KIA_MENU_H
