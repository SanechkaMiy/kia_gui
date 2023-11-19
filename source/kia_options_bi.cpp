#include "kia_options_bi.h"
#include "ui_kia_options_bi.h"

Kia_options_bi::Kia_options_bi(std::shared_ptr<Kia_settings> kia_settings,
                               std::shared_ptr<Client> client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kia_options_bi)
  , m_kia_settings(kia_settings)
  , m_client(client)
{
    ui->setupUi(this);
    m_layout_for_place_tab_widget = new QVBoxLayout(this);
    QStringList name_settings = {"Секундная метка", "Релейные команды"};
    m_bi_settings = new QTabWidget(this);
    m_layout_for_place_tab_widget->addWidget(m_bi_settings);
    for (uint16_t num_bi_settings = 0; num_bi_settings < constants::max_count_bi_settings; ++num_bi_settings)
    {
        m_tab_bi_settings[num_bi_settings] = new QWidget(this);
        m_bi_settings->addTab(m_tab_bi_settings[num_bi_settings], name_settings[num_bi_settings]);
        m_layout_for_relay_command.push_back(new QVBoxLayout(m_tab_bi_settings[num_bi_settings]));
    }
    bi_settings();
    relay_settings();
}

Kia_options_bi::~Kia_options_bi()
{
    delete ui;
}

void Kia_options_bi::bi_settings()
{
    QLabel* lb_set_period = new QLabel("Период секундной метки, мс", this);
    m_layout_for_relay_command[TBS_SEC_MARK]->addWidget(lb_set_period);
    QLineEdit* le_set_period = new QLineEdit("1000", this);
    m_layout_for_relay_command[TBS_SEC_MARK]->addWidget(le_set_period);
    connect(le_set_period, &QLineEdit::returnPressed, [this, le_set_period]()
    {
        m_kia_settings->m_kia_bi_settings->m_sec_mark_period = le_set_period->text().toInt();
        std::cout << m_kia_settings->m_kia_bi_settings->m_sec_mark_period << std::endl;
        QStringList sec_mark_period;

        sec_mark_period.push_back(QString::number(m_kia_settings->m_kia_bi_settings->m_sec_mark_period));
        m_client->send_data_to_server(SET_SEC_MARK_PERIOD, sec_mark_period);
    });
}

void Kia_options_bi::relay_settings()
{
    QStringList name_relay_command = {"Задать команду", "Длительность пульса, мс", "Полярность"};
    m_pb_relay_command[TBS_RELAY_COMMAND] = new QPushButton(name_relay_command[TRC_TIME_PULSE], this);
    m_layout_for_relay_command[TBS_RELAY_COMMAND]->addWidget(m_pb_relay_command[TRC_TIME_PULSE]);
    m_ledit_relay_pulse_time = new QLineEdit(this);
    m_layout_for_relay_command[TBS_RELAY_COMMAND]->addWidget(m_ledit_relay_pulse_time);

    m_pb_relay_command[TRC_PULSE] = new QPushButton(name_relay_command[TRC_PULSE], this);
    m_layout_for_relay_command[TBS_RELAY_COMMAND]->addWidget(m_pb_relay_command[TRC_PULSE]);
    m_ledit_relay_command = new QLineEdit(this);
    m_layout_for_relay_command[TBS_RELAY_COMMAND]->addWidget(m_ledit_relay_command);

    m_pb_relay_command[TRC_POLAR] = new QPushButton(name_relay_command[TRC_POLAR], this);
    m_layout_for_relay_command[TBS_RELAY_COMMAND]->addWidget(m_pb_relay_command[TRC_POLAR]);
    m_ledit_relay_polar = new QLineEdit(this);
    m_layout_for_relay_command[TBS_RELAY_COMMAND]->addWidget(m_ledit_relay_polar);

    std::vector<uint16_t> type_relay_command = {SET_RELAY_PULSE, SET_RELAY_PULSE_TIME, SET_RELAY_POLAR};
    for (uint16_t num_relay_command = 0; num_relay_command < constants::max_count_relay_command; ++num_relay_command)
    {

        connect(m_pb_relay_command[num_relay_command], &QPushButton::clicked, [this, type_relay_command, num_relay_command]()
        {
            //uint16_t relay_on_or_off = 0x0002;
            bool ok;
            uint16_t is_dec_or_hex = 0;
            switch(num_relay_command)
            {
            case TRC_PULSE:
                if ((m_ledit_relay_command->text()[0] == "0") && (m_ledit_relay_command->text()[1] == "x"))
                    is_dec_or_hex = 16;
                else
                    is_dec_or_hex = 10;

                m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command]  = m_ledit_relay_command->text().toUInt(&ok, is_dec_or_hex);
                printf("%04x\n", m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command]);
                break;
            case TRC_TIME_PULSE:
                m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command] = m_ledit_relay_pulse_time->text().toUInt();
                break;
            case TRC_POLAR:
                if ((m_ledit_relay_polar->text()[0] == "0") && (m_ledit_relay_polar->text()[1] == "x"))
                    is_dec_or_hex = 16;
                else
                    is_dec_or_hex = 10;
                m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command]  = m_ledit_relay_polar->text().toUInt(&ok, is_dec_or_hex);
                printf("%04x\n", m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command]);
                //                if (m_cb_polar->checkState() == Qt::CheckState::Checked)
                //                    m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command]  = 0x0f00;
                //                else
                //                    m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command] = 0x0000;

                break;
            }
            set_data_for_server(type_relay_command[num_relay_command], m_kia_settings->m_kia_data_to_server->m_param_relay_command);
        });
    }

}

void Kia_options_bi::check_state(uint16_t num_relay_command, uint16_t relay_command)
{
    m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command] = 0x0000;
    for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_ch)
    {
        if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_ch] == CS_IS_ON)
        {
            m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command] =
                    m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command] | (relay_command << (8 * num_ch));

        }
        else
        {
            m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command] =
                    m_kia_settings->m_kia_data_to_server->m_param_relay_command[num_relay_command] & ~(relay_command << (8 * num_ch));
        }
    }
}

template<typename Arr>
void Kia_options_bi::set_data_for_server(qint16 num, Arr &data_arr)
{
    QStringList data_for_client;
    uint16_t max_size = data_arr.size();
    for(int i = 0; i < max_size; ++i)
    {
        data_for_client.push_back(QString::number(data_arr[i]));
    }
    m_client->send_data_to_server(num, data_for_client);
}
