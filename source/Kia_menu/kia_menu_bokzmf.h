#ifndef KIA_MENU_BOKZMF_H
#define KIA_MENU_BOKZMF_H
#include "Kia_menu/kia_menu.h"
#include "Kia_main_struct.h"

class Kia_menu_bokzmf : public Kia_menu
{
public:
    Kia_menu_bokzmf(std::shared_ptr<Client> client);
    void create_action_state_work(QMenu* menu) override;
    void create_action_pci(QMenu* menu) override;
    void create_action_res(QMenu* menu) override;
    void create_action_commands(QMenu* menu) override;
    void create_action_get_frames(QMenu* menu) override;
private:
    std::shared_ptr<Client> m_client;
};

#endif // KIA_MENU_BOKZMF_H
