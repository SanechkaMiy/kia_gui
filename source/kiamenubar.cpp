#include "kiamenubar.h"
#include "ui_kiamenubar.h"

KiaMenuBar::KiaMenuBar(std::shared_ptr<Kia_settings> kia_settings,
                       std::shared_ptr<Client> client,
                       QWidget *parent)
    : QMenuBar(parent)
    , ui(new Ui::KiaMenuBar)
    , m_kia_settings(kia_settings)
    , m_client(client)
{
    ui->setupUi(this);

}

KiaMenuBar::~KiaMenuBar()
{
    delete ui;
}

QMenu *KiaMenuBar::get_menu_windows()
{
    return ui->menu_windows;
}


QMenu *KiaMenuBar::get_menu_settings()
{
    return ui->menu_settings;
}

QMenu *KiaMenuBar::get_menu_plots()
{
    return ui->menu_plots;
}

QMenu *KiaMenuBar::get_menu_tables()
{
    return ui->menu_tables;
}

QMenu *KiaMenuBar::get_menu_profile()
{
    return ui->menu_profile;
}

QMenu *KiaMenuBar::get_menu_commands()
{
    return ui->menu_commands;
}

void KiaMenuBar::create_actions(uint16_t type_bokz)
{
    m_kia_menu.reset(new Kia_menu_bokzm60(m_client));
    m_kia_menu->create_action_state_work(ui->menu_stated_work);
    m_kia_menu->create_action_pci(ui->menu_pci);
    m_kia_menu->create_action_res(ui->menu_res);
    m_kia_menu->create_action_commands(ui->menu_commands);

    ui->menu_commands->addAction("Отладочные команды", this, [this]()
    {
        emit show_kia_debug_command();
    });

    m_kia_menu->create_action_get_frames(ui->menu_get_frames);



    m_actions.push_back(std::make_pair(ui->menu_bi->title(), ui->menu_bi->actions()));
    m_actions.push_back(std::make_pair(ui->menu_stated_work->title(), ui->menu_stated_work->actions()));
    m_actions.push_back(std::make_pair(ui->menu_pci->title(), ui->menu_pci->actions()));
    m_actions.push_back(std::make_pair(ui->menu_res->title(), ui->menu_res->actions()));
    m_actions.push_back(std::make_pair(ui->menu_commands->title(), ui->menu_commands->actions()));
    m_actions.push_back(std::make_pair(ui->menu_get_frames->title(), ui->menu_get_frames->actions()));
}
void KiaMenuBar::load_mode_menu_bi()
{
    load_mods = true;
    if (m_kia_settings->m_kia_bi_settings->m_mode_kp > BI_ALL_OFF)
        m_kia_settings->m_kia_bi_settings->m_mode_kp = BI_ALL_OFF;
    set_mode_menu_bi(ui->set_power_main, ui->set_power_rezerv, m_kia_settings->m_kia_bi_settings->m_mode_kp);
    if (m_kia_settings->m_kia_bi_settings->m_mode_1s > BI_ALL_OFF)
        m_kia_settings->m_kia_bi_settings->m_mode_1s = BI_ALL_OFF;
    set_mode_menu_bi(ui->set_1s_main, ui->set_1s_rezerv, m_kia_settings->m_kia_bi_settings->m_mode_1s);
    load_mods = false;

}

std::vector<std::pair<QString, QList<QAction *> > > KiaMenuBar::get_menu_actions()
{
    return m_actions;
}

void KiaMenuBar::hide_or_show_actions(qint16 type_actions, qint16 num_actions, bool state)
{
    m_actions[type_actions].second[num_actions]->setVisible(state);
}


void KiaMenuBar::set_mode_menu_bi(QAction* main, QAction* rezerv, uint16_t mode)
{

    switch(mode)
    {
    case BI_MAIN_REZ_ON:
        main->setChecked(true);
        rezerv->setChecked(true);
        break;
    case BI_MAIN_ON:
        main->setChecked(true);
        rezerv->setChecked(false);
        break;
    case BI_REZERV_ON:
        main->setChecked(false);
        rezerv->setChecked(true);
        break;
    case BI_ALL_OFF:
        main->setChecked(false);
        rezerv->setChecked(false);
        break;
    }
}

void KiaMenuBar::on_state_on_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_STATE_ON, data_for_server);
}

void KiaMenuBar::on_state_off_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_STATE_OFF, data_for_server);
}

void KiaMenuBar::on_power_on_triggered()
{
    QStringList data_for_server;
    data_for_server.push_back(QString::number(m_kia_settings->m_kia_bi_settings->m_mode_kp));
    m_client->send_data_to_server(POWER_ON, data_for_server);
}

void KiaMenuBar::on_power_off_triggered()
{
    QStringList data_for_server;
    data_for_server.push_back(QString::number(m_kia_settings->m_kia_bi_settings->m_mode_kp));
    m_client->send_data_to_server(POWER_OFF, data_for_server);
}

void KiaMenuBar::on_set_power_main_toggled(bool arg1)
{
    if (!load_mods)
    {
        if(arg1)
            m_kia_settings->m_kia_bi_settings->m_mode_kp = m_kia_settings->m_kia_bi_settings->m_mode_kp - 2;
        else
            m_kia_settings->m_kia_bi_settings->m_mode_kp = m_kia_settings->m_kia_bi_settings->m_mode_kp + 2;
    }
}



void KiaMenuBar::on_set_power_rezerv_toggled(bool arg1)
{
    if (!load_mods)
    {
        if(arg1)
            m_kia_settings->m_kia_bi_settings->m_mode_kp--;
        else
            m_kia_settings->m_kia_bi_settings->m_mode_kp++;
    }
}

void KiaMenuBar::on_set_1s_main_toggled(bool arg1)
{
    if (!load_mods)
    {
        if(arg1)
            m_kia_settings->m_kia_bi_settings->m_mode_1s = m_kia_settings->m_kia_bi_settings->m_mode_1s - 2;
        else
            m_kia_settings->m_kia_bi_settings->m_mode_1s = m_kia_settings->m_kia_bi_settings->m_mode_1s + 2;
    }
}


void KiaMenuBar::on_set_1s_rezerv_toggled(bool arg1)
{
    if (!load_mods)
    {
        if(arg1)
            m_kia_settings->m_kia_bi_settings->m_mode_1s -= 1;
        else
            m_kia_settings->m_kia_bi_settings->m_mode_1s += 1;
    }
}

void KiaMenuBar::on_second_mark_on_triggered()
{
    QStringList data_for_server;
    data_for_server.push_back(QString::number(m_kia_settings->m_kia_bi_settings->m_mode_1s));
    m_client->send_data_to_server(ON_1S, data_for_server);
}

void KiaMenuBar::on_second_mark_off_triggered()
{
    QStringList data_for_server;
    data_for_server.push_back(QString::number(m_kia_settings->m_kia_bi_settings->m_mode_1s));
    m_client->send_data_to_server(OFF_1S, data_for_server);
}

void KiaMenuBar::on_set_auto_exp_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_OFFLINE_TEST, data_for_server);
}

void KiaMenuBar::on_set_to_define_address_dev_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_DEFINE_ADDRESS, data_for_server);
}

void KiaMenuBar::on_imitator_on_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(IMITATOR_ON, data_for_server);
}


void KiaMenuBar::on_imitator_off_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(IMITATOR_OFF, data_for_server);
}


void KiaMenuBar::on_control_power_on_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CONROL_COMMAND_ON, data_for_server);
}


void KiaMenuBar::on_control_power_off_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CONROL_COMMAND_OFF, data_for_server);
}


void KiaMenuBar::on_add_profile_triggered()
{
    emit show_kia_profile();
}


void KiaMenuBar::on_change_state_power_triggered()
{
    if (ui->set_power_main->isChecked())
        ui->set_power_main->setChecked(false);
    else
        ui->set_power_main->setChecked(true);

    if (ui->set_power_rezerv->isChecked())
        ui->set_power_rezerv->setChecked(false);
    else
        ui->set_power_rezerv->setChecked(true);
}


void KiaMenuBar::on_change_state_1s_triggered()
{
    if (ui->set_1s_main->isChecked())
        ui->set_1s_main->setChecked(false);
    else
        ui->set_1s_main->setChecked(true);

    if (ui->set_1s_rezerv->isChecked())
        ui->set_1s_rezerv->setChecked(false);
    else
        ui->set_1s_rezerv->setChecked(true);
}

