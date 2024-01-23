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

    create_ri_cyclogram_settings();
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
        if (load_data.size() == m_kia_settings->m_kia_bokz_settings->m_max_mpi_command)
        {
            for (uint16_t num_check_box = 0; num_check_box < m_kia_settings->m_kia_bokz_settings->m_max_mpi_command; ++num_check_box)
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
        break;
    case KNCycl_AI_USED_CYCL:
        if (load_data.size() == m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_ai)
        {
            for (uint16_t num_check_box = 0; num_check_box < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_ai; ++num_check_box)
            {
                if (load_data[num_check_box].toInt() == KiaS_SUCCESS)
                {
                    m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai[num_check_box] = KiaS_SUCCESS;
                    m_check_box_select_cyclograms_ai[num_check_box]->setCheckState(Qt::CheckState::Checked);
                }
                else
                {
                    m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai[num_check_box] = KiaS_FAIL;
                    m_check_box_select_cyclograms_ai[num_check_box]->setCheckState(Qt::CheckState::Unchecked);
                }
            }
            set_data_for_server(SET_DO_CYCLOGRAM_IN_AI, m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai);
        }
        break;
    }
}


void Kia_options_cyclograms::load_for_specific_cyclogram(qint16 type_cyclogram, QStringList load_data)
{
    if (load_data.size() == constants::max_count_param)
    {
        for (uint16_t ind_param = 0; ind_param < constants::max_count_param; ++ind_param)
        {
            m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][ind_param] = load_data[ind_param].toFloat();
            m_le_if_run_a_lot[type_cyclogram][ind_param]->setText(load_data[ind_param]);
        }
        load_data.push_front(QString::number(type_cyclogram));
        m_client->send_data_to_server(SET_CYCLOGRAM_SETTINGS_IF_DO_A_LOT, load_data);
    }
    else
        for (uint16_t ind_param = 0; ind_param < constants::max_count_param; ++ind_param)
            m_le_if_run_a_lot[type_cyclogram][ind_param]->setText("0");
}

void Kia_options_cyclograms::load_for_cyclogram_do_frames(qint16 type_settings, qint16 data)
{
    switch(type_settings)
    {
    case FS_TYPE_RECEIVE:
        m_cb_type_recieve->setCurrentIndex(data);
        m_kia_settings->m_kia_data_to_server->m_frame_type_recieve = data;
        m_client->send_data_to_server(SET_TYPE_FRAME_RECIEVE, QStringList(QString::number(m_kia_settings->m_kia_data_to_server->m_frame_type_recieve)));
        break;
    case FS_TYPE_FRAME:
        m_cb_type_frame->setCurrentIndex(data);
        m_kia_settings->m_kia_data_to_server->m_frame_type = data;
        m_client->send_data_to_server(SET_TYPE_FRAME, QStringList(QString::number(m_kia_settings->m_kia_data_to_server->m_frame_type)));
        break;
    }
}

void Kia_options_cyclograms::set_load_tp_settings(qint16 type_settings, QStringList load_data)
{
    switch(type_settings)
    {
    case USED_CYCLOGRAM:
        if (load_data.size() == m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp)
        {
            for (uint16_t num_check_box = 0; num_check_box < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp; ++num_check_box)
            {
                if (load_data[num_check_box].toInt() == KiaS_SUCCESS)
                {
                    m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp[num_check_box] = KiaS_SUCCESS;
                    m_check_box_select_cyclograms_tp[num_check_box]->setCheckState(Qt::CheckState::Checked);
                }
                else
                {
                    m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp[num_check_box] = KiaS_FAIL;
                    m_check_box_select_cyclograms_tp[num_check_box]->setCheckState(Qt::CheckState::Unchecked);
                }
            }
            set_data_for_server(SET_DO_CYCLOGRAM_IN_TP, m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_tp);
        }
        break;
    case COUNT_TO_DO_CYCLOGRAM:
        if (load_data.size() == m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp)
        {
            for (uint16_t num_le = 0; num_le < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp; ++num_le)
            {
                m_kia_settings->m_kia_data_to_server->m_count_to_do_cyclogram_in_tp[num_le] = load_data[num_le].toUInt();
                m_le_count_to_do_cyclograms[num_le]->setText(load_data[num_le]);
            }
        }
        else
            for (uint16_t num_le = 0; num_le < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp; ++num_le)
                m_le_count_to_do_cyclograms[num_le]->setText("100");
        set_data_for_server(SET_COUNT_TO_DO_CYCLOGRAM_IN_TP, m_kia_settings->m_kia_data_to_server->m_count_to_do_cyclogram_in_tp);
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

void Kia_options_cyclograms::set_load_regular_settings_do_command(qint16 type_cyclograms, qint16 type_settings, QStringList load_data)
{
    for (uint16_t num_command = 0; num_command < load_data.size(); num_command++)
    {
        QStringList data_for_client;
        switch(type_settings)
        {
        case USED_COMMAND:
            if (load_data[num_command].toInt() == KiaS_SUCCESS)
            {
                m_cb_for_change_do_cyclogram[type_cyclograms][num_command]->setCheckState(Qt::CheckState::Checked);
            }
            else
            {
                m_cb_for_change_do_cyclogram[type_cyclograms][num_command]->setCheckState(Qt::CheckState::Unchecked);
            }
            m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do[type_cyclograms][num_command] = load_data[num_command].toInt();
            data_for_client.push_back(QString::number(type_cyclograms));
            for(uint16_t i = 0; i < m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do[type_cyclograms].size(); ++i)
            {
                data_for_client.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do[type_cyclograms][i]));
            }
            m_client->send_data_to_server(SET_DO_CYCLOGRAM_IN_DO, data_for_client);
            break;
        case PAUSE_COMMAND:
            m_le_for_change_do_cyclogram[type_cyclograms][num_command]->setText(load_data[num_command]);
            m_kia_settings->m_kia_data_to_server->m_pause_to_do_cyclogram_in_do[type_cyclograms][num_command] = load_data[num_command].toInt();
            data_for_client.push_back(QString::number(type_cyclograms));
            for(uint16_t i = 0; i < m_kia_settings->m_kia_data_to_server->m_pause_to_do_cyclogram_in_do[type_cyclograms].size(); ++i)
            {
                data_for_client.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_pause_to_do_cyclogram_in_do[type_cyclograms][i]));
            }
            m_client->send_data_to_server(SET_PAUSE_DO_CYCLOGRAM_IN_DO, data_for_client);
            break;
        }
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
    m_layout_for_place_cyclogram_tab_widget[KNCycl_AI]->addWidget(m_check_box_continue_if_fails);
    auto* spacer = new QSpacerItem(20, 40, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_AI]->addItem(spacer);

    QLabel* label_name_settings =  new QLabel("Выполнение циклограмм:", this);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_AI]->addWidget(label_name_settings);
    for (uint16_t num_check_box = 0; num_check_box < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_ai; ++num_check_box)
    {
        m_check_box_select_cyclograms_ai.push_back(new QCheckBox(m_kia_settings->m_kia_gui_settings->m_cyclogram_ai_name[num_check_box].first, this));
        m_layout_for_place_cyclogram_tab_widget[KNCycl_AI]->addWidget(m_check_box_select_cyclograms_ai[num_check_box]);
        connect(m_check_box_select_cyclograms_ai[num_check_box], &QCheckBox::stateChanged, this, [this, num_check_box](int state)
        {
            if (state > 0)
                m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai[num_check_box] = KiaS_SUCCESS;
            else
                m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai[num_check_box] = KiaS_FAIL;
            set_data_for_server(SET_DO_CYCLOGRAM_IN_AI, m_kia_settings->m_kia_data_to_server->m_do_cyclogram_in_ai);
        });
        m_check_box_select_cyclograms_ai[num_check_box]->setCheckState(Qt::CheckState::Checked);
    }
}

void Kia_options_cyclograms::regular_settings()
{
    QTabWidget* tab_regular_cyclograms= new QTabWidget(this);
    auto main_widget_settings = new QWidget(this);
    tab_regular_cyclograms->addTab(main_widget_settings, "Основные настройки");
    auto main_layout_settings = new QVBoxLayout(main_widget_settings);
    m_layout_for_place_cyclogram_tab_widget[KNCycl_REGULAR]->addWidget(tab_regular_cyclograms);

    create_regular_cyclogram_settings(tab_regular_cyclograms);

    QLabel* label_name_settings =  new QLabel("Съем телеметрических массивов:", this);
    main_layout_settings->addWidget(label_name_settings);
    for (uint16_t num_check_box = 0; num_check_box < m_kia_settings->m_kia_bokz_settings->m_max_mpi_command; ++num_check_box)
    {
        m_check_box_select_mpi_command.push_back(new QCheckBox(m_kia_settings->m_kia_gui_settings->m_mpi_command_name[num_check_box].first, this));
        main_layout_settings->addWidget(m_check_box_select_mpi_command[num_check_box]);
        connect(m_check_box_select_mpi_command[num_check_box], &QCheckBox::stateChanged, this, [this, num_check_box](int state)
        {
            if (state > 0)
                m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram[num_check_box] = KiaS_SUCCESS;
            else
                m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram[num_check_box] = KiaS_FAIL;
            set_data_for_server(SET_USED_MPI_COMMAND_IN_CYCLOGRAM, m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram);
        });
    }
    m_check_box_select_mpi_command[MSHI_OR]->setCheckState(Qt::CheckState::Checked);
    //m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram[MSHI_OR] = KiaS_SUCCESS;
    //set_data_for_server(SET_USED_MPI_COMMAND_IN_CYCLOGRAM, m_kia_settings->m_kia_data_to_server->m_do_mpi_command_in_cyclogram);
    QLabel* label_change_frequency =  new QLabel("Изменение частоты обмена(Гц):", this);
    QLineEdit* line_edit_change_frequency = new QLineEdit("1", this);
    main_layout_settings->addWidget(label_change_frequency);
    main_layout_settings->addWidget(line_edit_change_frequency);
    connect(line_edit_change_frequency, &QLineEdit::returnPressed, [this, line_edit_change_frequency]()
    {
        m_kia_settings->m_kia_bokz_settings->m_freq_bokz = line_edit_change_frequency->text().toInt();
        QStringList freq_bokz;
        freq_bokz.push_back(QString::number(m_kia_settings->m_kia_bokz_settings->m_freq_bokz));
        m_client->send_data_to_server(SET_EXC_FREQ, freq_bokz);
    });
}

void Kia_options_cyclograms::create_regular_cyclogram_settings(QTabWidget* tab_regular_cyclogram)
{
    std::vector<QWidget*> widget_for_cyclogram_settings;
    std::vector<QGridLayout*> layout_for_cyclogram_settings;
    std::cout << m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name.size() << std::endl;
    m_cb_for_change_do_cyclogram.resize(m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name.size());
    m_le_for_change_do_cyclogram.resize(m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name.size());
    m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do.resize(m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name.size());
    m_kia_settings->m_kia_data_to_server->m_pause_to_do_cyclogram_in_do.resize(m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name.size());
    for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name.size(); ++num_cyclogram)
    {
        m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do[num_cyclogram].resize(m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name[num_cyclogram].size());
        m_kia_settings->m_kia_data_to_server->m_pause_to_do_cyclogram_in_do[num_cyclogram].resize(m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name[num_cyclogram].size());
        widget_for_cyclogram_settings.push_back(new QWidget(this));
        layout_for_cyclogram_settings.push_back(new QGridLayout(widget_for_cyclogram_settings[num_cyclogram]));
        tab_regular_cyclogram->addTab(widget_for_cyclogram_settings[num_cyclogram],
                                      m_kia_settings->m_kia_gui_settings->m_cyclogram_tp_name[num_cyclogram].first);
        QLabel* m_le_name_settings = new QLabel("Выполнение команд и пауза(мкс)", this);
        layout_for_cyclogram_settings[num_cyclogram]->addWidget(m_le_name_settings, 0, 0);
        for (uint16_t num_command = 0; num_command < m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name[num_cyclogram].size(); ++num_command)
        {
            m_cb_for_change_do_cyclogram[num_cyclogram].push_back(new QCheckBox(m_kia_settings->m_kia_gui_settings->m_cyclogram_do_name[num_cyclogram][num_command].first, widget_for_cyclogram_settings[num_cyclogram]));
            m_le_for_change_do_cyclogram[num_cyclogram].push_back(new QLineEdit("0", widget_for_cyclogram_settings[num_cyclogram]));
            layout_for_cyclogram_settings[num_cyclogram]->addWidget(m_cb_for_change_do_cyclogram[num_cyclogram][num_command], num_command + 1, 0);
            layout_for_cyclogram_settings[num_cyclogram]->addWidget(m_le_for_change_do_cyclogram[num_cyclogram][num_command], num_command + 1, 1);
            connect(m_cb_for_change_do_cyclogram[num_cyclogram][num_command], &QCheckBox::stateChanged, this, [this, num_cyclogram, num_command](int state)
            {
                if (state > 0)
                    m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do[num_cyclogram][num_command] = KiaS_SUCCESS;
                else
                    m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do[num_cyclogram][num_command] = KiaS_FAIL;

                QStringList data_for_client;
                data_for_client.push_back(QString::number(num_cyclogram));
                for(int i = 0; i < m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do[num_cyclogram].size(); ++i)
                {
                    data_for_client.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_do_cyclograms_in_do[num_cyclogram][i]));
                }
                m_client->send_data_to_server(SET_DO_CYCLOGRAM_IN_DO, data_for_client);

            });
            m_cb_for_change_do_cyclogram[num_cyclogram][num_command]->setCheckState(Qt::CheckState::Checked);

            connect(m_le_for_change_do_cyclogram[num_cyclogram][num_command], &QLineEdit::returnPressed, [this, num_cyclogram, num_command]()
            {
                m_kia_settings->m_kia_data_to_server->m_pause_to_do_cyclogram_in_do[num_cyclogram][num_command] = m_le_for_change_do_cyclogram[num_cyclogram][num_command]->text().toInt();
                QStringList data_for_client;
                data_for_client.push_back(QString::number(num_cyclogram));
                for(int i = 0; i < m_kia_settings->m_kia_data_to_server->m_pause_to_do_cyclogram_in_do[num_cyclogram].size(); ++i)
                {
                    data_for_client.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_pause_to_do_cyclogram_in_do[num_cyclogram][i]));
                }
                m_client->send_data_to_server(SET_PAUSE_DO_CYCLOGRAM_IN_DO, data_for_client);
            });

        }
    }
}

void Kia_options_cyclograms::create_ri_cyclogram_settings()
{
    m_le_if_run_a_lot.resize(m_kia_settings->m_kia_gui_settings->m_cyclogram_ri_name.size());
    m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot.resize(m_kia_settings->m_kia_gui_settings->m_cyclogram_ri_name.size());
    for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_settings->m_kia_gui_settings->m_cyclogram_ri_name.size(); num_cyclogram++)
    {
        cyclogram_settings_if_run_a_lot(m_kia_settings->m_kia_gui_settings->m_cyclogram_ri_name[num_cyclogram].first, num_cyclogram);
    }
    cyclogram_tp();
    cyclogram_do_frames();
}

void Kia_options_cyclograms::cyclogram_settings_if_run_a_lot(QString name_cyclogram, uint16_t type_cyclogram)
{
    m_map_key_cyclogram_ri[m_kia_settings->m_kia_gui_settings->m_cyclogram_ri_name[type_cyclogram].second] = type_cyclogram;

    widget_for_ri_cyclogram_settings.push_back(new QWidget(this));
    layout_for_ri_cyclogram_settings.push_back(new QVBoxLayout(widget_for_ri_cyclogram_settings[type_cyclogram]));
    m_cyclogram_settings->addTab(widget_for_ri_cyclogram_settings[type_cyclogram], name_cyclogram);
    std::vector<QLabel*> label_name_settings;
    QStringList list_name_settings = {"Количество:", "Период(сек):", "Время(мин):"};

    for (uint16_t ind_param = 0; ind_param < constants::max_count_param; ++ind_param)
    {
        label_name_settings.push_back(new QLabel(list_name_settings[ind_param], this));

        m_le_if_run_a_lot[type_cyclogram].push_back(new QLineEdit("0", this));
        m_le_if_run_a_lot[type_cyclogram][SPC_COUNT]->setToolTip("Установите 0, для бесконечного выполнения");
        m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][ind_param] = 1;
        connect(m_le_if_run_a_lot[type_cyclogram][ind_param], &QLineEdit::returnPressed, [this, ind_param, type_cyclogram]()
        {
            m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][ind_param] = m_le_if_run_a_lot[type_cyclogram][ind_param]->text().toFloat();
            switch(ind_param)
            {
            case SPC_COUNT:
                m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_DURATION] = (m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_COUNT]
                                                                                                             * m_le_if_run_a_lot[type_cyclogram][SPC_PERIOD]->text().toFloat()) / 60;
                m_le_if_run_a_lot[type_cyclogram][SPC_DURATION]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_DURATION] / 60));
                break;
            case SPC_PERIOD:
                m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_DURATION] = (m_le_if_run_a_lot[type_cyclogram][SPC_COUNT]->text().toFloat()
                                                                                                             * m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_PERIOD]) / 60;
                m_le_if_run_a_lot[type_cyclogram][SPC_DURATION]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_DURATION] / 60));
                break;
            case SPC_DURATION:
                m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_COUNT] = (m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_DURATION] * 60)
                        / m_le_if_run_a_lot[type_cyclogram][SPC_PERIOD]->text().toFloat();
                m_le_if_run_a_lot[type_cyclogram][SPC_COUNT]->setText(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][SPC_COUNT]));
                break;
            }
            QStringList data_for_client;
            data_for_client.push_back(QString::number(type_cyclogram));
            for(uint16_t i = 0; i < m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram].size(); ++i)
            {
                data_for_client.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_param_for_run_a_lot[type_cyclogram][i]));
            }
            m_client->send_data_to_server(SET_CYCLOGRAM_SETTINGS_IF_DO_A_LOT, data_for_client);
        });
        layout_for_ri_cyclogram_settings[type_cyclogram]->addWidget(label_name_settings[ind_param]);
        layout_for_ri_cyclogram_settings[type_cyclogram]->addWidget(m_le_if_run_a_lot[type_cyclogram][ind_param]);

    }
}

void Kia_options_cyclograms::cyclogram_tp()
{
    QLabel* label_name_settings =  new QLabel("Выполнение циклограмм:", this);

    QGridLayout* lay = new QGridLayout();


    for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp; ++num_cyclogram)
    {
        m_check_box_select_cyclograms_tp.push_back(new QCheckBox(m_kia_settings->m_kia_gui_settings->m_cyclogram_tp_name[num_cyclogram].first, this));
        m_le_count_to_do_cyclograms.push_back(new QLineEdit("100", this));
        m_kia_settings->m_kia_data_to_server->m_count_to_do_cyclogram_in_tp.push_back(100);
        m_le_count_to_do_cyclograms[num_cyclogram]->setEnabled(false);
        lay->addWidget(m_check_box_select_cyclograms_tp[num_cyclogram], num_cyclogram, USED_CYCLOGRAM);
        lay->addWidget(m_le_count_to_do_cyclograms[num_cyclogram], num_cyclogram, COUNT_TO_DO_CYCLOGRAM);
        connect(m_check_box_select_cyclograms_tp[num_cyclogram], &QCheckBox::stateChanged, this, [this, num_cyclogram](int state)
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
        if (num_cyclogram != m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp - 1)
            m_check_box_select_cyclograms_tp[num_cyclogram]->setCheckState(Qt::CheckState::Checked);
    }
    m_check_box_off_power_for_tp = new QCheckBox("Выключить питание после завершения", this);
    if (m_kia_settings->m_kia_gui_settings->m_cyclogram_ri_name.size() != 0)
    {
        layout_for_ri_cyclogram_settings[m_map_key_cyclogram_ri[CYCLOGRAM_TECH_RUN]]->addWidget(label_name_settings);
        layout_for_ri_cyclogram_settings[m_map_key_cyclogram_ri[CYCLOGRAM_TECH_RUN]]->addLayout(lay);
        layout_for_ri_cyclogram_settings[m_map_key_cyclogram_ri[CYCLOGRAM_TECH_RUN]]->addWidget(m_check_box_off_power_for_tp);

    }
    else
    {
        label_name_settings->setVisible(false);
        for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp; ++num_cyclogram)
        {
            m_check_box_select_cyclograms_tp[num_cyclogram]->setVisible(false);
            m_le_count_to_do_cyclograms[num_cyclogram]->setVisible(false);
        }
        m_check_box_off_power_for_tp->setVisible(false);
    }
    connect(m_check_box_off_power_for_tp, &QCheckBox::stateChanged, this, [this](int state)
    {
        m_kia_settings->m_kia_data_to_server->m_off_power_for_tp = state;
        m_client->send_data_to_server(SET_IS_OFF_POWER_IN_TP, QStringList(QString::number(state)));
    });
}

void Kia_options_cyclograms::cyclogram_do_frames()
{
    QLabel* label_frame_type_recive_settings =  new QLabel("Тип приема кадра:", this);
    m_cb_type_recieve = new QComboBox(this);
    m_cb_type_recieve->setEditable(true);
    QStringList type_recieve = {"Прием по МКО", "Прием по FTID-(USB)"};
    for (auto el : type_recieve)
        m_cb_type_recieve->addItem(el);
    m_cb_type_recieve->setMaxVisibleItems(type_recieve.size());
    QLabel* label_frame_type_settings =  new QLabel("Тип кадра:", this);
    m_cb_type_frame = new QComboBox(this);
    m_cb_type_frame->setEditable(true);
    QStringList type_frame = {"Полный кадр", "Бинированный кадр"};
    for (auto el : type_frame)
        m_cb_type_frame->addItem(el);
    m_cb_type_frame->setMaxVisibleItems(type_frame.size());

    connect(m_cb_type_recieve, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index)
    {
        m_kia_settings->m_kia_data_to_server->m_frame_type_recieve = index;
        m_client->send_data_to_server(SET_TYPE_FRAME_RECIEVE, QStringList(QString::number(m_kia_settings->m_kia_data_to_server->m_frame_type_recieve)));
    });

    connect(m_cb_type_frame, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index)
    {
        m_kia_settings->m_kia_data_to_server->m_frame_type = index;
        m_client->send_data_to_server(SET_TYPE_FRAME, QStringList(QString::number(m_kia_settings->m_kia_data_to_server->m_frame_type_recieve)));
    });
    if (m_kia_settings->m_kia_gui_settings->m_cyclogram_ri_name.size() != 0)
    {
        layout_for_ri_cyclogram_settings[m_map_key_cyclogram_ri[CYCL_FULL_FRAMES]]->addWidget(label_frame_type_recive_settings);
        layout_for_ri_cyclogram_settings[m_map_key_cyclogram_ri[CYCL_FULL_FRAMES]]->addWidget(m_cb_type_recieve);
        layout_for_ri_cyclogram_settings[m_map_key_cyclogram_ri[CYCL_FULL_FRAMES]]->addWidget(label_frame_type_settings);
        layout_for_ri_cyclogram_settings[m_map_key_cyclogram_ri[CYCL_FULL_FRAMES]]->addWidget(m_cb_type_frame);
    }
    else
    {
        label_frame_type_recive_settings->setVisible(false);
        label_frame_type_settings->setVisible(false);
        m_cb_type_recieve->setVisible(false);
        m_cb_type_frame->setVisible(false);
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
