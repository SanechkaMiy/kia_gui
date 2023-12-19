#include "kia_options_cyclograms.h"
#include "ui_kia_options_cyclograms.h"

Kia_options_cyclograms::Kia_options_cyclograms(std::shared_ptr<Kia_settings> kia_settings, std::shared_ptr<Client> client, QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::Kia_options_cyclograms)
  , m_kia_settings(kia_settings)
  , m_client(client)
{
    ui->setupUi(this);
    m_layout_for_place_tab_widget = new QVBoxLayout(this);
    m_cyclogram_settings = new QTabWidget(this);
    m_layout_for_place_tab_widget->addWidget(m_cyclogram_settings);
    for (uint16_t num_cyclograms = 0; num_cyclograms < constants::max_count_cyclograms; ++num_cyclograms)
    {
        m_tab_cyclograms[num_cyclograms] = new QWidget(this);
        m_cyclogram_settings->addTab(m_tab_cyclograms[num_cyclograms], m_kia_settings->m_kia_bokz_settings->m_name_cyclograms[num_cyclograms]);
        m_layout_for_place_cyclogram_tab_widget.push_back(new QVBoxLayout(m_tab_cyclograms[num_cyclograms]));
    }
    ai_settings();
    regular_settings();
    cyclogram_settings_if_run_a_lot(m_le_technical_run_settings, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run, KNCycl_TR, SET_TP_SETTINGS);
    cyclogram_settings_if_run_a_lot(m_le_zkr_settings, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr, KNCycl_ZKR, SET_ZKR_SETTINGS);
    cyclogram_settings_if_run_a_lot(m_le_full_frames_settings, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames, KNCycl_FRAMES, SET_FULL_FRAMES_SETTINGS);
    cyclogram_tp();
}

Kia_options_cyclograms::~Kia_options_cyclograms()
{
    delete ui;
}

void Kia_options_cyclograms::set_load_settings(qint16 type_load, QStringList load_data)
{
    switch(type_load)
    {
    case KNCycl_AI:
        if (load_data.size() != 0)
        {
            m_check_box_continue_if_fails->setChecked(load_data[0].toInt());
            m_client->send_data_to_server(SET_AI_SKIP_OR_STOP, QStringList(load_data[0]));
        }
        else
            m_check_box_continue_if_fails->setChecked(true);
        break;
    case KNCycl_REGULAR:
        if (load_data.size() != 0)
        {
            for (uint16_t num_check_box = 0; num_check_box < constants::max_mpi_command; ++num_check_box)
            {
                if (load_data[num_check_box].toInt() == KiaS_SUCCESS)
                {
                    m_check_box_select_mpi_command[num_check_box]->setCheckState(Qt::CheckState::Checked);
                }
                else
                {
                    m_check_box_select_mpi_command[num_check_box]->setCheckState(Qt::CheckState::Unchecked);
                }
            }
        }
        else
            for (uint16_t num_check_box = 0; num_check_box < constants::max_mpi_command; ++num_check_box)
                m_check_box_select_mpi_command[num_check_box]->setCheckState(Qt::CheckState::Unchecked);
        break;
    case KNCycl_TR:
        load_for_specific_cyclogram(load_data, m_le_technical_run_settings, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run, SET_TP_SETTINGS);
    case KNCycl_ZKR:
        load_for_specific_cyclogram(load_data, m_le_zkr_settings, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr, SET_ZKR_SETTINGS);
        break;
    case KNCycl_FRAMES:
        load_for_specific_cyclogram(load_data, m_le_full_frames_settings, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames, SET_FULL_FRAMES_SETTINGS);
        break;
    }
}


void Kia_options_cyclograms::load_for_specific_cyclogram(QStringList load_data, std::vector<QLineEdit *> &le_settings, std::array<float, constants::max_count_param> &param, uint16_t type_to_send)
{
    if (load_data.size() != 0)
    {
        for (uint16_t ind_param = 0; ind_param < constants::max_count_param; ++ind_param)
        {
            param[ind_param] = load_data[ind_param].toFloat();
            le_settings[ind_param]->setText(load_data[ind_param]);
        }
        m_client->send_data_to_server(type_to_send, load_data);
    }
    else
        for (uint16_t ind_param = 0; ind_param < constants::max_count_param; ++ind_param)
            le_settings[ind_param]->setText("0");
}

void Kia_options_cyclograms::set_load_tp_settings(qint16 type_settings, QStringList load_data)
{
    switch(type_settings)
    {
    case USED_CYCLOGRAM:
        if (load_data.size() != 0)
        {
            for (uint16_t num_check_box = 0; num_check_box < constants::max_count_cyclograms_in_tp; ++num_check_box)
            {
                if (load_data[num_check_box].toInt() == KiaS_SUCCESS)
                {
                    m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp[num_check_box] = KiaS_SUCCESS;
                    m_check_box_select_cyclograms[num_check_box]->setCheckState(Qt::CheckState::Checked);
                }
                else
                {
                    m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp[num_check_box] = KiaS_FAIL;
                    m_check_box_select_cyclograms[num_check_box]->setCheckState(Qt::CheckState::Unchecked);
                }
            }
            set_data_for_server(SET_DO_CYCLOGRAM_IN_TP, m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp);
        }
        else
            for (uint16_t num_check_box = 0; num_check_box < constants::max_count_cyclograms_in_tp; ++num_check_box)
                m_check_box_select_cyclograms[num_check_box]->setCheckState(Qt::CheckState::Unchecked);
        break;
    case COUNT_TO_DO_CYCLOGRAM:
        if (load_data.size() != 0)
        {
            for (uint16_t num_le = 0; num_le < constants::max_count_cyclograms_in_tp; ++num_le)
            {
                m_kia_settings->m_kia_data_to_server->m_count_to_do_cyclogram_in_tp[num_le] = load_data[num_le].toUInt();
                m_le_count_to_do_cyclograms[num_le]->setText(load_data[num_le]);
            }
        }
        else
            for (uint16_t num_le = 0; num_le < constants::max_count_cyclograms_in_tp; ++num_le)
                m_le_count_to_do_cyclograms[num_le]->setText("100");
        break;
    case OFF_POWER:
        if (load_data.size() != 0)
        {
            m_check_box_off_power_for_tp->setChecked(load_data[0].toInt());
            m_kia_settings->m_kia_data_to_server->m_off_power_for_tp = load_data[0].toInt();
            m_client->send_data_to_server(SET_IS_OFF_POWER_IN_TP, QStringList(load_data[0]));
        }
        else
            m_check_box_off_power_for_tp->setChecked(true);
        break;
    }
}

void Kia_options_cyclograms::ai_settings()
{
    m_check_box_continue_if_fails = new QCheckBox("Продолжить, если ошибка", this);
    m_check_box_continue_if_fails->setChecked(true);
    connect(m_check_box_continue_if_fails, &QCheckBox::stateChanged, this, [this](int state)
    {
        m_kia_settings->m_kia_data_to_server->m_skip_fails_for_continue = state;
        m_client->send_data_to_server(SET_AI_SKIP_OR_STOP, QStringList(QString::number(state)));
    });
    //m_check_box_continue_if_fails->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_AI]->addWidget(m_check_box_continue_if_fails);
    auto* spacer = new QSpacerItem(20, 40, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_AI]->addItem(spacer);
}

void Kia_options_cyclograms::regular_settings()
{
    QLabel* label_name_settings =  new QLabel("Съем телеметрических массивов:", this);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_REGULAR]->addWidget(label_name_settings);
    for (uint16_t num_check_box = 0; num_check_box < constants::max_mpi_command; ++num_check_box)
    {
        m_check_box_select_mpi_command[num_check_box] = new QCheckBox(m_kia_settings->m_kia_gui_settings->m_mpi_command_name[num_check_box], this);
        m_layout_for_place_cyclogram_tab_widget[KNCycl_REGULAR]->addWidget(m_check_box_select_mpi_command[num_check_box]);
        connect(m_check_box_select_mpi_command[num_check_box], &QCheckBox::stateChanged, this, [this, num_check_box](int state)
        {
            if (state > 0)
                m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram[num_check_box] = KiaS_SUCCESS;
            else
                m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram[num_check_box] = KiaS_FAIL;
            set_data_for_server(SET_USED_MPI_COMMAND_IN_CYCLOGRAM, m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram);
        });
    }
    QLabel* label_change_frequency =  new QLabel("Изменение частоты обмена(Гц):", this);
    QLineEdit* line_edit_change_frequency = new QLineEdit("1", this);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_REGULAR]->addWidget(label_change_frequency);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_REGULAR]->addWidget(line_edit_change_frequency);
    connect(line_edit_change_frequency, &QLineEdit::returnPressed, [this, line_edit_change_frequency]()
    {
        m_kia_settings->m_kia_bokz_settings->m_freq_bokz = line_edit_change_frequency->text().toInt();
        std::cout << m_kia_settings->m_kia_bokz_settings->m_freq_bokz << std::endl;
        QStringList freq_bokz;
        freq_bokz.push_back(QString::number(m_kia_settings->m_kia_bokz_settings->m_freq_bokz));
        m_client->send_data_to_server(SET_EXC_FREQ, freq_bokz);
    });
}

void Kia_options_cyclograms::cyclogram_settings_if_run_a_lot(std::vector<QLineEdit *>& le_settings, std::array<float, constants::max_count_param>& param,
                                                             uint16_t type_settings, uint16_t type_to_send)
{
    std::vector<QLabel*> label_name_settings;
    QStringList list_name_settings = {"Количество:", "Период(сек):", "Время(мин):"};
    for (uint16_t ind_param = 0; ind_param < constants::max_count_param; ++ind_param)
    {
        label_name_settings.push_back(new QLabel(list_name_settings[ind_param], this));

        le_settings.push_back(new QLineEdit("0", this));
        le_settings[SPC_COUNT]->setToolTip("Установите 0, для бесконечного выполнения");
        param[ind_param] = 1;
        connect(le_settings[ind_param], &QLineEdit::returnPressed, [this, ind_param, &le_settings, &param, type_to_send]() mutable
        {
            param[ind_param] = le_settings[ind_param]->text().toFloat();
            switch(ind_param)
            {
            case SPC_COUNT:
                param[SPC_DURATION] = (param[SPC_COUNT] * le_settings[SPC_PERIOD]->text().toFloat()) / 60;
                le_settings[SPC_DURATION]->setText(QString::number(param[SPC_DURATION] / 60));
                break;
            case SPC_PERIOD:
                param[SPC_DURATION] = (le_settings[SPC_COUNT]->text().toFloat() * param[SPC_PERIOD]) / 60;
                le_settings[SPC_DURATION]->setText(QString::number(param[SPC_DURATION] / 60));
                break;
            case SPC_DURATION:
                param[SPC_COUNT] = (param[SPC_DURATION] * 60) / le_settings[SPC_PERIOD]->text().toFloat();
                le_settings[SPC_COUNT]->setText(QString::number(param[SPC_COUNT]));
                break;
            }
            set_data_for_server(type_to_send, param);
        });
        m_layout_for_place_cyclogram_tab_widget[type_settings]->addWidget(label_name_settings[ind_param]);
        m_layout_for_place_cyclogram_tab_widget[type_settings]->addWidget(le_settings[ind_param]);

    }
}

void Kia_options_cyclograms::cyclogram_tp()
{
    QLabel* label_name_settings =  new QLabel("Выполнение циклограмм:", this);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_TR]->addWidget(label_name_settings);
    QGridLayout* lay = new QGridLayout();
    m_layout_for_place_cyclogram_tab_widget[KNCycl_TR]->addLayout(lay);
    for (uint16_t num_cyclogram = 0; num_cyclogram < constants::max_count_cyclograms_in_tp; ++num_cyclogram)
    {
        m_check_box_select_cyclograms[num_cyclogram] = new QCheckBox(m_kia_settings->m_kia_gui_settings->m_cyclogram_name[num_cyclogram], this);
        m_le_count_to_do_cyclograms[num_cyclogram] = new QLineEdit("100", this);
        m_kia_settings->m_kia_data_to_server->m_count_to_do_cyclogram_in_tp[num_cyclogram] = 100;
        m_le_count_to_do_cyclograms[num_cyclogram]->setEnabled(false);
        lay->addWidget(m_check_box_select_cyclograms[num_cyclogram], num_cyclogram, USED_CYCLOGRAM);
        lay->addWidget(m_le_count_to_do_cyclograms[num_cyclogram], num_cyclogram, COUNT_TO_DO_CYCLOGRAM);
        connect(m_check_box_select_cyclograms[num_cyclogram], &QCheckBox::stateChanged, this, [this, num_cyclogram](int state)
        {
            if (state > 0)
            {
                m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp[num_cyclogram] = KiaS_SUCCESS;
                m_le_count_to_do_cyclograms[num_cyclogram]->setEnabled(true);
            }
            else
            {
                m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp[num_cyclogram] = KiaS_FAIL;
                m_le_count_to_do_cyclograms[num_cyclogram]->setEnabled(false);
            }
            set_data_for_server(SET_DO_CYCLOGRAM_IN_TP, m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp);
        });
        connect(m_le_count_to_do_cyclograms[num_cyclogram], &QLineEdit::returnPressed, [this, num_cyclogram]()
        {
            m_kia_settings->m_kia_data_to_server->m_count_to_do_cyclogram_in_tp[num_cyclogram] = m_le_count_to_do_cyclograms[num_cyclogram]->text().toInt();
            set_data_for_server(SET_COUNT_TO_DO_CYCLOGRAM_IN_TP, m_kia_settings->m_kia_data_to_server->m_count_to_do_cyclogram_in_tp);
        });
    }
    m_check_box_off_power_for_tp = new QCheckBox("Выключить питание после завершения", this);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_TR]->addWidget(m_check_box_off_power_for_tp);
    connect(m_check_box_off_power_for_tp, &QCheckBox::stateChanged, this, [this](int state)
    {
        m_kia_settings->m_kia_data_to_server->m_off_power_for_tp = state;
        m_client->send_data_to_server(SET_IS_OFF_POWER_IN_TP, QStringList(QString::number(state)));
    });
}


template<typename Arr>
void Kia_options_cyclograms::set_data_for_server(qint16 num, Arr &data_arr)
{
    QStringList data_for_client;
    uint16_t max_size = data_arr.size();
    for(int i = 0; i < max_size; ++i)
    {
        data_for_client.push_back(QString::number(data_arr[i]));
    }
    m_client->send_data_to_server(num, data_for_client);
}
