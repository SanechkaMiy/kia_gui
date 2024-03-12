#include "kiawindowsettings.h"
#include "ui_kiawindowsettings.h"

KiaWindowSettings::KiaWindowSettings(std::shared_ptr<Kia_settings> kia_settings, QWidget *parent) :
    QDialog(parent)
  , m_kia_settings(kia_settings)
  , ui(new Ui::KiaWindowSettings)
{
    ui->setupUi(this);
    m_layout_for_place_table_settings = new QHBoxLayout(this);
    m_set_table = new QTableWidget(this);
    m_layout_for_place_table_settings->addWidget(m_set_table);
}

KiaWindowSettings::~KiaWindowSettings()
{
    delete ui;
}

void KiaWindowSettings::create_table_settings(qint16 type_bokz)
{
    m_set_table->setColumnCount(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_set_table->setRowCount(m_kia_settings->m_kia_bokz_settings->m_bokz_row_name[type_bokz].size());
    m_kia_settings->m_kia_data_to_server->m_qa.resize(constants::size_qa + 1);
    m_kia_settings->m_kia_data_to_server->m_w.resize(constants::size_w + 1);
    m_mpi_num.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    for (int row = 0; row < m_kia_settings->m_kia_bokz_settings->m_bokz_row_name[type_bokz].size(); ++row)
    {
        auto item_vertical_header = new QTableWidgetItem(m_kia_settings->m_kia_bokz_settings->m_bokz_row_name[type_bokz][row]);
        m_set_table->setVerticalHeaderItem(row, item_vertical_header);
        item_vertical_header->setTextAlignment(Qt::AlignCenter);
    }
    for (int coll = 0; coll < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++coll)
    {
        m_set_table->setHorizontalHeaderItem(coll, new QTableWidgetItem(m_kia_settings->m_kia_bokz_settings->m_bokz_type[type_bokz]));
        m_check_box_used.push_back(new QCheckBox());
        m_check_box_used[coll]->setStyleSheet("margin-left:5%;");
        m_combo_box_address.push_back(new QComboBox());
        m_combo_box_address[coll]->setEditable(true);

        m_combo_box_mpi.push_back(new QComboBox());
        m_combo_box_mpi[coll]->setEditable(true);

        m_combo_box_lpi.push_back(new QComboBox());
        m_combo_box_lpi[coll]->setEditable(true);

        m_cob_used_bi.push_back(new QComboBox());
        m_cob_used_bi[coll]->setEditable(true);

        m_cob_num_used_channel.push_back(new QComboBox());
        m_cob_num_used_channel[coll]->setEditable(true);

        m_combo_box_td.push_back(new QComboBox());
        m_combo_box_td[coll]->setEditable(true);

        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_combo_box_address[coll]->setMaxVisibleItems(m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi]);
        m_combo_box_mpi[coll]->setMaxVisibleItems(m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi]);
        m_combo_box_lpi[coll]->setMaxVisibleItems(m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi]);
        m_combo_box_td[coll]->setMaxVisibleItems(m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi]);
        m_cob_num_used_channel[coll]->setMaxVisibleItems(m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi]);
        connect(m_check_box_used[coll], &QCheckBox::toggled,  ([this, coll](bool is_toggled)
        {
            m_kia_settings->m_kia_data_to_server->m_is_used_bokz[coll] = is_toggled;
            set_data_for_server(SET_USED_BOKZ, m_kia_settings->m_kia_data_to_server->m_is_used_bokz);
        }));
        connect(m_combo_box_address[coll], &QComboBox::currentTextChanged, [this, coll](const QString & is_changed)
        {
            m_kia_settings->m_kia_data_to_server->m_address_change[coll] = is_changed.toInt();
            set_data_for_server(SET_USED_ADDRESS, m_kia_settings->m_kia_data_to_server->m_address_change);
        });
        connect(m_combo_box_lpi[coll], QOverload<int>::of(&QComboBox::currentIndexChanged), [this, coll](int index)
        {
            m_kia_settings->m_kia_data_to_server->m_lpi_change[coll] = index;
            set_data_for_server(SET_CURRENT_LPI, m_kia_settings->m_kia_data_to_server->m_lpi_change);
        });

        connect(m_combo_box_mpi[coll], QOverload<int>::of(&QComboBox::currentIndexChanged), [this, coll](int index)
        {
            m_kia_settings->m_kia_data_to_server->m_mpi_num[coll] = m_mpi_num[index];
            m_kia_settings->m_kia_data_to_server->m_mpi_num_index_of_num_bokz[coll] = index;
            set_data_for_server(SET_NUM_MPI, m_kia_settings->m_kia_data_to_server->m_mpi_num);
        });

        connect(m_cob_used_bi[coll], QOverload<int>::of(&QComboBox::currentIndexChanged), [this, coll](int index)
        {
            m_kia_settings->m_kia_data_to_server->m_num_used_bi[coll] = index;
            set_data_for_server(SET_NUM_BI, m_kia_settings->m_kia_data_to_server->m_num_used_bi);
        });

        connect(m_cob_num_used_channel[coll], QOverload<int>::of(&QComboBox::currentIndexChanged), [this, coll](int index)
        {
            m_kia_settings->m_kia_data_to_server->m_num_used_channel[coll] = index;
            set_data_for_server(SET_USED_CHANNEL, m_kia_settings->m_kia_data_to_server->m_num_used_channel);
        });

        connect(m_combo_box_td[coll], &QComboBox::currentTextChanged, [this, coll](const QString & is_changed)
        {
            m_kia_settings->m_kia_data_to_server->m_td_change[coll] = is_changed.toInt();
            set_data_for_server(SET_TD, m_kia_settings->m_kia_data_to_server->m_td_change);
        });
        QStringList lpi_descr = {"A", "B"};
        for (uint16_t num = 0; num < constants::max_count_address; ++num)
        {
            m_combo_box_address[coll]->addItem(QString::number(num));
            if (num < constants::max_count_lpi)
                m_combo_box_lpi[coll]->addItem(lpi_descr[num]);
            if (num < constants::max_count_td)
                m_combo_box_td[coll]->addItem(QString::number(num + 1));
        }
        for (int num_ch = 0; num_ch < m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi]; ++num_ch)
        {
            m_cob_num_used_channel[coll]->addItem(QString::number(num_ch + 1));
        }

        m_set_table->setCellWidget(TS_USED_BOKZ, coll, m_check_box_used[coll]);
        m_set_table->setCellWidget(TS_ADDRESS, coll, m_combo_box_address[coll]);
        m_set_table->setCellWidget(TS_MPI, coll, m_combo_box_mpi[coll]);
        m_set_table->setCellWidget(TS_LPI, coll, m_combo_box_lpi[coll]);
        m_set_table->setCellWidget(TS_TYPE_BI, coll, m_cob_used_bi[coll]);
        m_set_table->setCellWidget(TS_NUM_CH, coll, m_cob_num_used_channel[coll]);
        m_set_table->setCellWidget(TS_TD, coll, m_combo_box_td[coll]);
    }
    emit send_value_width_for_state_table(m_set_table->verticalHeader()->sizeHint().width(), m_set_table->columnWidth(0));
}

void KiaWindowSettings::set_data_table_settings(QStringList data_from_server)
{
    for (int coll = 0; coll < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++coll)
    {
        {
            QString name_mpi;
            switch(data_from_server[0].toInt())
            {
            case TS_USED_BOKZ:
                if (data_from_server[coll + 1].toInt() == CS_IS_ON)
                {
                    m_check_box_used[coll]->setCheckState(Qt::CheckState::Checked);
                }
                break;
            case TS_ADDRESS:
                m_combo_box_address[coll]->setCurrentIndex(data_from_server[coll + 1].toInt());
                break;
            case TS_MPI:
                if (data_from_server[1].toStdString() == "load")
                {
                    m_combo_box_mpi[coll]->setCurrentIndex(data_from_server[coll + 2].toInt());
                }
                else
                {
                    for (int i = 1; i < data_from_server.size(); ++i)
                    {
                        m_mpi_num[i - 1] = data_from_server[i].toInt();
                        if (data_from_server[i].toInt() < constants::MAX_TMK_NUMBER)
                        {
                            name_mpi = "tmk ";
                            m_combo_box_mpi[coll]->addItem(name_mpi + data_from_server[i]);
                        }
                        else
                        {
                            name_mpi = "tmkUsb ";
                            m_combo_box_mpi[coll]->addItem(name_mpi + data_from_server[i]);

                        }
                    }
                }
                break;
            case TS_LPI:
                m_combo_box_lpi[coll]->setCurrentIndex(data_from_server[coll + 1].toInt());
                break;
            case TS_TYPE_BI:
                if (data_from_server[1].toStdString() == "load")
                {
                    m_cob_used_bi[coll]->setCurrentIndex(data_from_server[coll + 2].toInt());
                }
                else
                {
                    for (int ind_data = 1; ind_data < data_from_server.size(); ++ind_data)
                    {
                        m_cob_used_bi[coll]->addItem(m_kia_settings->m_kia_bi_settings->m_bi_type[m_kia_settings->m_type_bi] + " " + data_from_server[ind_data]);
                    }
                }
                break;
            case TS_NUM_CH:
                if (data_from_server[1].toStdString() == "load")
                {
                    m_cob_num_used_channel[coll]->setCurrentIndex(data_from_server[coll + 2].toInt());
                }
                break;
            }
        }
    }
}

template <typename Arr>
void KiaWindowSettings::set_data_for_server(qint16 num, Arr &data_arr)
{
    QStringList data_for_client;
    uint16_t max_size = data_arr.size();
    for(int i = 0; i < max_size; ++i)
    {
        data_for_client.push_back(QString::number(data_arr[i]));
    }
    emit send_data_from_client(num, data_for_client);
}


