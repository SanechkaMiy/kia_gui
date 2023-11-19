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
namespace Ui {
class KiaMenuBar;
}

class KiaMenuBar : public QMenuBar
{
    Q_OBJECT

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

    void load_mode_menu_bi();
signals:
    void show_kia_profile();
private slots:
    void on_power_on_triggered();
    void on_power_off_triggered();
    void on_second_mark_on_triggered();
    void on_second_mark_off_triggered();
    void on_state_on_triggered();
    void on_state_off_triggered();
    void on_set_no_triggered();
    void on_set_to_triggered();
    void on_set_loc_triggered();
    void on_set_auto_exp_triggered();
    void on_set_shtmi1_triggered();
    void on_set_shtmi2_triggered();
    void on_set_mshior_triggered();
    void on_set_dtmi_triggered();
    void on_set_smti_triggered();
    void on_set_vmti_triggered();
    void on_set_synchro_triggered();
    void on_set_skor_triggered();
    void on_command_no_triggered();
    void on_command_to_triggered();
    void on_command_loc_triggered();
    void on_command_otclp_triggered();
    void on_set_to_define_address_dev_triggered();
    void on_command_os_triggered();
    void on_command_vsk_triggered();
    void on_full_exp_triggered();

    void on_set_tech_run_triggered();

    void on_set_cycl_zkr_triggered();

    void on_set_ful_frame_triggered();

    void on_imitator_on_triggered();

    void on_imitator_off_triggered();

    void on_control_power_on_triggered();

    void on_control_power_off_triggered();

    void on_set_power_main_toggled(bool arg1);

    void on_set_power_rezerv_toggled(bool arg1);

    void on_set_1s_main_toggled(bool arg1);

    void on_set_1s_rezerv_toggled(bool arg1);

    void on_add_profile_triggered();

private:
    void set_mode_menu_bi(QAction* main, QAction* rezerv, uint16_t mode);
    void create_action();
    Ui::KiaMenuBar *ui;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    QAction* m_action_for_num_mpi;
    QMenu * m_edit_context_menu;
    QPushButton* m_pb_for_delete_plots;
    bool load_mods = false;
};

#endif // KIAMENUBAR_H
