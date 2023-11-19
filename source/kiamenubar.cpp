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
    create_action();
}


void KiaMenuBar::create_action()
{
    ui->menu_pci->addAction("Тест участка включения", this, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_STATE_ON, data_for_server);
    });
    ui->menu_pci->addSeparator();
    ui->menu_pci->addAction("Тест проверки адресов", this, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_TEST_ADRESS, data_for_server);
    });
    ui->menu_pci->addAction("Тест МПИ", this, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_TEST_MKO, data_for_server);
    });
    ui->menu_pci->addAction("Тест 1с метки", this, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_1S_MARK, data_for_server);
    });
    ui->menu_pci->addAction("Тест функционирования", this, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_OPERATION, data_for_server);
    });
    ui->menu_pci->addAction("Тест Синхро", this, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_SYNCHRO, data_for_server);
    });
    ui->menu_pci->addSeparator();
    ui->menu_pci->addAction("Тест участка выключения", this, [this]()
    {
        QStringList data_for_server;
        m_client->send_data_to_server(CYCLOGRAM_STATE_OFF, data_for_server);
    });
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


void KiaMenuBar::on_set_shtmi1_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(SHTMI_1, data_for_server);
}

void KiaMenuBar::on_set_shtmi2_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(SHTMI_2, data_for_server);
}

void KiaMenuBar::on_set_mshior_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(MSHI_OR, data_for_server);
}

void KiaMenuBar::on_set_dtmi_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(DTMI_ONE, data_for_server);
}

void KiaMenuBar::on_set_smti_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(SMTI, data_for_server);
}

void KiaMenuBar::on_set_vmti_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(VMTI, data_for_server);
}

void KiaMenuBar::on_set_synchro_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(SYNCHRO, data_for_server);
}

void KiaMenuBar::on_set_skor_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(SKOR, data_for_server);
}

void KiaMenuBar::on_set_no_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_NO, data_for_server);
}

void KiaMenuBar::on_set_to_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_TO, data_for_server);
}

void KiaMenuBar::on_set_loc_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_LOC, data_for_server);
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

void KiaMenuBar::on_full_exp_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_DO_EXPOSURE, data_for_server);
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

void KiaMenuBar::on_command_no_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(COMMAND_NO, data_for_server);
}

void KiaMenuBar::on_command_to_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(COMMAND_TO, data_for_server);
}

void KiaMenuBar::on_command_loc_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(COMMAND_LOC, data_for_server);
}

void KiaMenuBar::on_command_otclp_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(COMMAND_OTCLP, data_for_server);
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

void KiaMenuBar::on_command_os_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(COMMAND_OS, data_for_server);
}

void KiaMenuBar::on_command_vsk_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(COMMAND_VSKOU, data_for_server);
}

void KiaMenuBar::on_set_tech_run_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_TECH_RUN, data_for_server);
}

void KiaMenuBar::on_set_cycl_zkr_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(CYCLOGRAM_ZKR, data_for_server);
}

void KiaMenuBar::on_set_ful_frame_triggered()
{
    QStringList data_for_server;
    m_client->send_data_to_server(DO_FULL_FRAME, data_for_server);

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

