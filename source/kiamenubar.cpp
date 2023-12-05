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
    create_action_state_work();
    create_action_pci();
    create_action_res();
    create_action_commands();
    create_action_get_frames();
}


void KiaMenuBar::create_action_pci()
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
    m_actions.push_back(std::make_pair(ui->menu_pci->title(), ui->menu_pci->actions()));
}

void KiaMenuBar::create_action_res()
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> res_action;
    res_action.push_back(std::make_tuple("Испытание крышки", QKeySequence(), CYCLOGRAM_ZKR));
    res_action.push_back(std::make_tuple("Технологический прогон", QKeySequence(), CYCLOGRAM_TECH_RUN));
    res_action.push_back(std::make_tuple("Получение темновых кадров", QKeySequence(), CYCL_FULL_FRAMES));
    for (auto& el : res_action)
    {
        auto action = ui->menu_res->addAction(std::get<NAME_ACTION>(el), this, [this, el]()
        {
            QStringList data_for_server;
            m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
        });
        action->setShortcut(std::get<HOT_KEY>(el));
    }
    m_actions.push_back(std::make_pair(ui->menu_res->title(), ui->menu_res->actions()));
}

void KiaMenuBar::create_action_commands()
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> commands_action;
    commands_action.push_back(std::make_tuple("ШТМИ1", QKeySequence(Qt::Key_F2), SHTMI_1));
    commands_action.push_back(std::make_tuple("ШТМИ2", QKeySequence(Qt::Key_F3), SHTMI_2));
    commands_action.push_back(std::make_tuple("МШИ ОР", QKeySequence(Qt::Key_F4), MSHI_OR));
    commands_action.push_back(std::make_tuple("ДТМИ", QKeySequence(Qt::Key_F5), DTMI_ONE));
    commands_action.push_back(std::make_tuple("СМТИ", QKeySequence(), SMTI));
    commands_action.push_back(std::make_tuple("ВМТИ", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("seperator", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("Команда СИНХРО", QKeySequence(Qt::Key_F7), SYNCHRO));
    commands_action.push_back(std::make_tuple("Команда СКОР", QKeySequence(), SKOR));
    commands_action.push_back(std::make_tuple("Команда НО", QKeySequence(), COMMAND_NO));
    commands_action.push_back(std::make_tuple("Команда ТО", QKeySequence(), COMMAND_TO));
    commands_action.push_back(std::make_tuple("Команда ЛОК", QKeySequence(), COMMAND_LOC));
    commands_action.push_back(std::make_tuple("Команда ОТКЛ Р", QKeySequence(), COMMAND_OTCLP));
    commands_action.push_back(std::make_tuple("seperator", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("Команда ОС", QKeySequence(), COMMAND_OS));
    commands_action.push_back(std::make_tuple("Команда ВСКОУ", QKeySequence(), COMMAND_VSKOU));
    commands_action.push_back(std::make_tuple("seperator", QKeySequence(), VMTI));
    commands_action.push_back(std::make_tuple("Полная экспозиция", QKeySequence(), CYCLOGRAM_DO_EXPOSURE));
    for (auto& el : commands_action)
    {
        if (std::get<NAME_ACTION>(el) == "seperator")
        {
            ui->menu_commands->addSeparator();
        }
        else
        {
            auto action = ui->menu_commands->addAction(std::get<NAME_ACTION>(el), this, [this, el]()
            {
                QStringList data_for_server;
                m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
            });
            action->setShortcut(std::get<HOT_KEY>(el));
        }
    }
    m_actions.push_back(std::make_pair(ui->menu_commands->title(), ui->menu_commands->actions()));
}

void KiaMenuBar::create_action_get_frames()
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> frames_action;
    frames_action.push_back(std::make_tuple("Полный кадр", QKeySequence(), DO_FULL_FRAME));
    for (auto& el : frames_action)
    {
        auto action = ui->menu_get_frames->addAction(std::get<NAME_ACTION>(el), this, [this, el]()
        {
            QStringList data_for_server;
            m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
        });
        action->setShortcut(std::get<HOT_KEY>(el));
    }
    m_actions.push_back(std::make_pair(ui->menu_get_frames->title(), ui->menu_get_frames->actions()));
}

void KiaMenuBar::create_action_state_work()
{
    std::vector<std::tuple<QString, QKeySequence, uint16_t>> stated_work_action;
    stated_work_action.push_back(std::make_tuple("Начальная ориентация (НО)", QKeySequence(Qt::CTRL + Qt::Key_N), CYCLOGRAM_NO));
    stated_work_action.push_back(std::make_tuple("Текущая ориентация (ТО)", QKeySequence(Qt::CTRL + Qt::Key_T), CYCLOGRAM_TO));
    stated_work_action.push_back(std::make_tuple("Локализация (ЛОК)", QKeySequence(Qt::CTRL + Qt::Key_L), CYCLOGRAM_LOC));
    for (auto& el : stated_work_action)
    {
        auto action = ui->menu_stated_work->addAction(std::get<NAME_ACTION>(el), this, [this, el]()
        {
            QStringList data_for_server;
            m_client->send_data_to_server(std::get<NUM_COMMAND>(el), data_for_server);
        });
        action->setShortcut(std::get<HOT_KEY>(el));
    }
    m_actions.push_back(std::make_pair(ui->menu_stated_work->title(), ui->menu_stated_work->actions()));
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

std::vector<std::pair<QString, QList<QAction *> > > KiaMenuBar::get_menu_actions()
{
    return m_actions;
}

void KiaMenuBar::hide_or_show_actions(qint16 type_actions, qint16 num_actions, bool state)
{
     m_actions[type_actions].second[num_actions]->setVisible(state);
//    if (!state)
//        m_actions[type_actions].second[num_actions]->setVisible(false);
//    else
//        m_actions[type_actions].second[num_actions]->setVisible(true);
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

