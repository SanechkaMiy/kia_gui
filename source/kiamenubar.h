#ifndef KIAMENUBAR_H
#define KIAMENUBAR_H

#include <QMenuBar>
#include <QEvent>
#include <QCloseEvent>
#include <iostream>
#include "client.h"
#include "Kia_main_struct.h"
#include <functional>
#include <vector>
#include "Kia_menu/kia_menu.h"
namespace Ui {
class KiaMenuBar;
}

class KiaMenuBar : public QMenuBar
{
    Q_OBJECT
    enum st_work_action
    {
        NAME_ACTION = 0,
        HOT_KEY = 1,
        NUM_COMMAND = 2,
    };

public:
    explicit KiaMenuBar(std::shared_ptr<Kia_settings> kia_settings,
                        std::shared_ptr<Client> client,
                        QWidget *parent = nullptr);
    ~KiaMenuBar();
    QMenu* get_menu_windows();
    QMenu* get_menu_settings();
    QMenu* get_menu_plots();
    QMenu* get_menu_tables();
    QMenu* get_menu_profile();
    QMenu* get_menu_commands();

    void create_actions();
    void load_mode_menu_bi();
    std::vector<std::pair<QString, QList<QAction*>>> get_menu_actions();

    std::vector<QMenu*> get_menu_from_menubar();
public slots:
    void hide_or_show_actions(qint16 type_actions, qint16 num_actions, bool state);
    void hide_or_show_menu(qint16 type_menu, bool state);
signals:
    void show_kia_profile();
    void show_kia_debug_command();
private slots:
    void on_power_on_triggered();
    void on_power_off_triggered();
    void on_second_mark_on_triggered();
    void on_second_mark_off_triggered();
    void on_set_auto_exp_triggered();
    void on_set_to_define_address_dev_triggered();

    void on_imitator_on_triggered();

    void on_imitator_off_triggered();

    void on_control_power_on_triggered();

    void on_control_power_off_triggered();

    void on_set_power_main_toggled(bool arg1);

    void on_set_power_rezerv_toggled(bool arg1);

    void on_set_1s_main_toggled(bool arg1);

    void on_set_1s_rezerv_toggled(bool arg1);

    void on_add_profile_triggered();

    void on_change_state_power_triggered();

    void on_change_state_1s_triggered();

private:
    void set_mode_menu_bi(QAction* main, QAction* rezerv, uint16_t mode);
    Ui::KiaMenuBar *ui;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    std::shared_ptr<Kia_menu> m_kia_menu;
    QAction* m_action_for_num_mpi;
    QMenu * m_edit_context_menu;
    QPushButton* m_pb_for_delete_plots;
    bool load_mods = false;
    std::vector<std::pair<QString, QList<QAction*>>> m_actions;
    std::vector<QMenu*> m_menu_bar_list;
};

#endif // KIAMENUBAR_H
