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
    regular_settings();
    technical_run_settings();
    zkr_settings();
    frames_settings();
}

Kia_options_cyclograms::~Kia_options_cyclograms()
{
    delete ui;
}

void Kia_options_cyclograms::set_load_settings(qint16 type_load, QStringList load_data)
{
    switch(type_load)
    {
    case KNCycl_REGULAR:
        if (load_data.size() != 0)
        {
            for (uint16_t num_check_box = 0; num_check_box < constants::max_mpi_command; ++num_check_box)
            {
                if (load_data[num_check_box].toInt() == KiaS_SUCCESS)
                    m_check_box_select_mpi_command[num_check_box]->setCheckState(Qt::CheckState::Checked);
                else
                    m_check_box_select_mpi_command[num_check_box]->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        else
            for (uint16_t num_check_box = 0; num_check_box < constants::max_mpi_command; ++num_check_box)
                m_check_box_select_mpi_command[num_check_box]->setCheckState(Qt::CheckState::Unchecked);
        break;
    case KNCycl_ZKR:
        if (load_data.size() != 0)
        {
            for (uint16_t ind_zkr_param = 0; ind_zkr_param < constants::max_count_param; ++ind_zkr_param)
                m_le_zkr_settings[ind_zkr_param]->setText(load_data[ind_zkr_param]);
        }
        else
            for (uint16_t ind_zkr_param = 0; ind_zkr_param < constants::max_count_param; ++ind_zkr_param)
                m_le_zkr_settings[ind_zkr_param]->setText("0");
        break;
    case KNCycl_FRAMES:
        if (load_data.size() != 0)
        {
            for (uint16_t ind_zkr_param = 0; ind_zkr_param < constants::max_count_param; ++ind_zkr_param)
                m_le_full_frames_settings[ind_zkr_param]->setText(load_data[ind_zkr_param]);
        }
        else
            for (uint16_t ind_zkr_param = 0; ind_zkr_param < constants::max_count_param; ++ind_zkr_param)
                m_le_full_frames_settings[ind_zkr_param]->setText("0");
        break;
    }
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
            emit set_mpi_command_for_cyclogram();
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

void Kia_options_cyclograms::technical_run_settings()
{
    std::vector<QLabel*> label_name_settings;
    QStringList list_name_settings = {"Количество:", "Период(сек):", "Время(мин):"};
    for (uint16_t ind_param = 0; ind_param < constants::max_count_param; ++ind_param)
    {
        label_name_settings.push_back(new QLabel(list_name_settings[ind_param], this));
        m_le_technical_run_settings.push_back(new QLineEdit("0", this));
        m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[ind_param] = 1;
        connect(m_le_technical_run_settings[ind_param], &QLineEdit::returnPressed, [this, ind_param]()
        {
            m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[ind_param] = m_le_technical_run_settings[ind_param]->text().toInt();
            switch(ind_param)
            {
            case SPC_COUNT:
                if (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_COUNT] != 0)
                    m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_PERIOD] = (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_DURATION] * 60) / m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_COUNT];
                else
                {
                    m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_PERIOD] = 1;
                }
                m_le_technical_run_settings[SPC_PERIOD]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_PERIOD]));
                break;
            case SPC_PERIOD:
                m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_DURATION] =  (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_COUNT] * m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_PERIOD]);
                m_le_technical_run_settings[SPC_DURATION]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_DURATION] / 60));
                break;
            case SPC_DURATION:
                m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_COUNT] = (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_DURATION] * 60) / m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_PERIOD];
                m_le_technical_run_settings[SPC_COUNT]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run[SPC_COUNT]));
                break;
            }
            set_data_for_server(SET_TR_SETTINGS, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_tech_run);
        });
        m_layout_for_place_cyclogram_tab_widget[KNCycl_TR]->addWidget(label_name_settings[ind_param]);
        m_layout_for_place_cyclogram_tab_widget[KNCycl_TR]->addWidget(m_le_technical_run_settings[ind_param]);

    }
}

void Kia_options_cyclograms::zkr_settings()
{
    std::vector<QLabel*> label_name_settings;
    QStringList list_name_settings = {"Количество:", "Период(сек):", "Время(мин):"};
    for (uint16_t ind_param = 0; ind_param < constants::max_count_param; ++ind_param)
    {
        label_name_settings.push_back(new QLabel(list_name_settings[ind_param], this));
        m_le_zkr_settings.push_back(new QLineEdit("0", this));
        m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[ind_param] = 1;
        connect(m_le_zkr_settings[ind_param], &QLineEdit::returnPressed, [this, ind_param]()
        {
            m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[ind_param] = m_le_zkr_settings[ind_param]->text().toInt();
            switch(ind_param)
            {
            case SPC_COUNT:
                if (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_COUNT] != 0)
                    m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_PERIOD] = (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_DURATION] * 60) / m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_COUNT];
                else
                {
                    m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_PERIOD] = 1;
                }
                m_le_zkr_settings[SPC_PERIOD]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_PERIOD]));
                break;
            case SPC_PERIOD:
                m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_DURATION] =  (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_COUNT] * m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_PERIOD]);
                m_le_zkr_settings[SPC_DURATION]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_DURATION] / 60));
                break;
            case SPC_DURATION:
                m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_COUNT] = (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_DURATION] * 60) / m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_PERIOD];
                m_le_zkr_settings[SPC_COUNT]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_COUNT]));
                break;
            }
            set_data_for_server(SET_ZKR_SETTINGS, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr);
        });
        m_layout_for_place_cyclogram_tab_widget[KNCycl_ZKR]->addWidget(label_name_settings[ind_param]);
        m_layout_for_place_cyclogram_tab_widget[KNCycl_ZKR]->addWidget(m_le_zkr_settings[ind_param]);

    }
}

void Kia_options_cyclograms::frames_settings()
{
    std::vector<QLabel*> label_name_settings;
    QStringList list_name_settings = {"Количество:", "Период(сек):", "Время(мин):"};
    for (uint16_t ind_zkr_param = 0; ind_zkr_param < constants::max_count_param; ++ind_zkr_param)
    {
        label_name_settings.push_back(new QLabel(list_name_settings[ind_zkr_param], this));

        m_le_full_frames_settings.push_back(new QLineEdit("0", this));
        m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[ind_zkr_param] = 1;
        connect(m_le_full_frames_settings[ind_zkr_param], &QLineEdit::returnPressed, [this, ind_zkr_param]()
        {
            m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[ind_zkr_param] = m_le_full_frames_settings[ind_zkr_param]->text().toInt();
            switch(ind_zkr_param)
            {
            case SPC_COUNT:
                if (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[SPC_COUNT] != 0)
                    m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[SPC_PERIOD] = (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_DURATION] * 60) / m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[SPC_COUNT];
                else
                {
                    m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[SPC_PERIOD] = 1;
                }
                m_le_full_frames_settings[SPC_PERIOD]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_PERIOD]));
                break;
            case SPC_PERIOD:
                m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[SPC_DURATION] =  (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_COUNT] * m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[SPC_PERIOD]);
                m_le_full_frames_settings[SPC_DURATION]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_DURATION] / 60));
                break;
            case SPC_DURATION:
                m_kia_settings->m_kia_data_to_server->m_param_for_cycl_full_frames[SPC_COUNT] = (m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_DURATION] * 60) / m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_PERIOD];
                m_le_full_frames_settings[SPC_COUNT]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr[SPC_COUNT]));
                break;
            }
            set_data_for_server(SET_FULL_FRAMES_SETTINGS, m_kia_settings->m_kia_data_to_server->m_param_for_cycl_zkr);
        });
        m_layout_for_place_cyclogram_tab_widget[KNCycl_FRAMES]->addWidget(label_name_settings[ind_zkr_param]);
        m_layout_for_place_cyclogram_tab_widget[KNCycl_FRAMES]->addWidget(m_le_full_frames_settings[ind_zkr_param]);

    }
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
