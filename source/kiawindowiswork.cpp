#include "kiawindowiswork.h"
#include "ui_kiawindowiswork.h"
KiaWindowIsWork::KiaWindowIsWork(std::shared_ptr<Kia_settings> kia_settings,
                                 std::shared_ptr<Client> client, QWidget *parent) :
    QDialog(parent)
  , m_kia_settings(kia_settings)
  , m_client(client)
  , ui(new Ui::KiaWindowIsWork)
{
    ui->setupUi(this);
    //m_layout_for_place_window_is_work = new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);
    m_pb_stop = new QPushButton("Стоп!");

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Space), m_pb_stop);
    connect(shortcut, &QShortcut::activated, this, [this]()
    {
        set_stop_slot();
    });

    m_label_db = new QLabel("БД", this);
    m_kled_status_db = new KLed(this);
    m_kled_status_db->off();

    m_label_console = new QLabel("Ядро", this);
    m_kled_status_connect_to_console = new KLed(this);
    m_kled_status_connect_to_console->off();

    m_kled_statuc_connect.push_back(m_kled_status_connect_to_console);
    m_kled_statuc_connect.push_back(m_kled_status_db);

    connect(m_pb_stop, &QPushButton::clicked, this, [this]()
    {
        set_stop_slot();
    });
    m_cb_is_otclp = new QCheckBox("ОТКЛР", this);
    connect(m_cb_is_otclp, &QCheckBox::stateChanged, this, [this](int state)
    {
        m_is_otclp = state;
    });

}
KiaWindowIsWork::~KiaWindowIsWork()
{
    delete ui;
}

void KiaWindowIsWork::create_table_status_bokz()
{
    m_set_table = new QTableWidget(this);
    ui->layout_table->addWidget(m_set_table);
    //m_set_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_set_table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_set_table->setColumnCount(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_set_table->setRowCount(m_kia_settings->m_kia_bokz_settings->m_bokz_status_row_name[m_kia_settings->m_type_bokz].size());
    for (int row = 0; row < m_kia_settings->m_kia_bokz_settings->m_bokz_status_row_name[m_kia_settings->m_type_bokz].size(); ++row)
    {
        auto item_vertical_header = new QTableWidgetItem(m_kia_settings->m_kia_bokz_settings->m_bokz_status_row_name[m_kia_settings->m_type_bokz][row]);
        m_set_table->setVerticalHeaderItem(row, item_vertical_header);
        item_vertical_header->setTextAlignment(Qt::AlignCenter);
    }
    for (int coll = 0; coll < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++coll)
    {
        m_set_table->setHorizontalHeaderItem(coll, new QTableWidgetItem(m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]));
        m_line_edit_bshv.push_back(new QLineEdit());
        m_line_edit_bshv[coll]->setReadOnly(false);

        m_line_edit_st1.push_back(new QLineEdit());

        m_line_edit_st2.push_back(new QLineEdit());

        m_set_table->setCellWidget(ST_BSHV, coll, m_line_edit_bshv[coll]);
        m_set_table->setCellWidget(ST_ST1, coll, m_line_edit_st1[coll]);
        m_set_table->setCellWidget(ST_ST2, coll, m_line_edit_st2[coll]);
        connect(m_line_edit_bshv[coll], &QLineEdit::selectionChanged, [this]()
        {
            m_is_set_data_bshv = false;
        });
        connect(m_line_edit_bshv[coll], &QLineEdit::returnPressed, [this, coll]()
        {
            m_is_set_data_bshv = true;
            for (int coll_used = 0; coll_used < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++coll_used)
            {
                if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[coll_used] == CS_IS_ON)
                {
                    m_line_edit_bshv[coll_used]->setText(m_line_edit_bshv[coll]->text());
                }
            }
            QStringList data_for_client;
            data_for_client.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_num_used_bi[coll]));
            data_for_client.push_back(QString::number(m_line_edit_bshv[coll]->text().toInt()));
            m_client->send_data_to_server(SET_BSHV, data_for_client);
        });
    }

}

void KiaWindowIsWork::create_status_bi()
{

    for (int row = 0; row < m_kia_settings->m_kia_bi_settings->m_count_bi; ++row)
    {

        ui->layout_status_info->addWidget(m_label_db);
        ui->layout_status_info->addWidget(m_kled_status_db);

        ui->layout_status_info->addWidget(m_label_console);
        ui->layout_status_info->addWidget(m_kled_status_connect_to_console);

        ui->layout_status_info->addWidget(m_cb_is_otclp);
        ui->layout_status_info->addWidget(m_pb_stop);
    }
    emit send_widget(this);
}


void KiaWindowIsWork::check_connect(qint16 type_kled, qint16 is_con_to_core)
{
    KLed::State kled_state;
    if (is_con_to_core == CS_IS_ON)
        kled_state = KLed::State::On;
    else
        kled_state = KLed::State::Off;
    m_kled_statuc_connect[type_kled]->setState(kled_state);
}

void KiaWindowIsWork::set_data_to_table(QStringList data)
{
    QString str_status;
    QPalette pallete_status_on;
    pallete_status_on.setColor(QPalette::Base, Qt::green);

    QPalette pallete_status_cold;
    pallete_status_cold.setColor(QPalette::Base, Qt::blue);

    QPalette pallete_status_off;
    pallete_status_off.setColor(QPalette::Base, Qt::red);

    QPalette pallete_status_default;
    pallete_status_default.setColor(QPalette::Base, Qt::white);

    if (data[0].toInt() == ST_BSHV && m_is_set_data_bshv)
    {
        m_line_edit_bshv[data[1].toInt()]->setText(data[2]);
    }

    if (data[0].toInt() == ST_ST1 && m_is_set_data_bshv)
    {
        if (!data[2].isEmpty())
        {
            if (data[2][2] == "e")
                m_line_edit_st1[data[1].toInt()]->setPalette(pallete_status_on);
            else if(data[2][2] == "2")
                m_line_edit_st1[data[1].toInt()]->setPalette(pallete_status_cold);
            else
                m_line_edit_st1[data[1].toInt()]->setPalette(pallete_status_off);
        }
        else
            m_line_edit_st1[data[1].toInt()]->setPalette(pallete_status_default);
        m_line_edit_st1[data[1].toInt()]->setText(data[2]);
    }

    if (data[0].toInt() == ST_ST2 && m_is_set_data_bshv)
    {
        m_line_edit_st2[data[1].toInt()]->setText(data[2]);
    }
}

void KiaWindowIsWork::set_stop_slot()
{
    emit set_stop(m_is_otclp);
}

void KiaWindowIsWork::set_width_for_vertical_header(qint16 width_header, qint16 width_col)
{
    m_set_table->verticalHeader()->setFixedWidth(width_header);
    for (int coll = 0; coll < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++coll)
    {
        m_set_table->setColumnWidth(coll, width_col);
    }
}
