#include "kia_options_interface.h"
#include "ui_kia_options_interface.h"

Kia_options_interface::Kia_options_interface(std::shared_ptr<Kia_settings> kia_settings,
                                             std::shared_ptr<Client> client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kia_options_interface),
    m_kia_settings(kia_settings),
    m_client(client)
{
    ui->setupUi(this);

}

Kia_options_interface::~Kia_options_interface()
{
    delete ui;
}

void Kia_options_interface::create_window_state_settings(QStringList name_tables, QVector<QStringList> rows_from_table)
{
    ui->lw_name_table->addItems(name_tables);
    m_cb_for_data.resize(rows_from_table.size());
    m_cb_for_color.resize(rows_from_table.size());
    m_kia_settings->m_kia_gui_settings->m_status_for_table_state.resize(name_tables.size());
    m_kia_settings->m_kia_gui_settings->m_color_for_table_state.resize(name_tables.size());
    m_status.resize(name_tables.size());
    m_color.resize(name_tables.size());
    QStringList coll_name = {"Отображение", "Цвет"};
    for (uint16_t num_table = 0; num_table < name_tables.size(); ++num_table)
    {
        m_table.push_back(new QTableWidget(this));
        m_table[num_table]->hide();
        m_table[num_table]->setColumnCount(2);
        m_table[num_table]->setRowCount(rows_from_table[num_table].size());
        for (uint16_t coll = 0; coll < m_table[num_table]->columnCount(); coll++)
            m_table[num_table]->setHorizontalHeaderItem(coll, new QTableWidgetItem(coll_name[coll]));
        for (uint16_t num_row = 0; num_row < rows_from_table[num_table].size(); ++num_row)
        {
            auto item_vertical_header = new QTableWidgetItem(rows_from_table[num_table][num_row]);
            m_table[num_table]->setVerticalHeaderItem(num_row, item_vertical_header);
            m_cb_for_data[num_table].push_back(new QCheckBox(this));
            m_cb_for_color[num_table].push_back(new QCheckBox(this));
            m_kia_settings->m_kia_gui_settings->m_status_for_table_state[num_table].push_back("1");
            m_kia_settings->m_kia_gui_settings->m_color_for_table_state[num_table].push_back("1");
            m_cb_for_data[num_table][num_row]->hide();
            m_cb_for_data[num_table][num_row]->setChecked(true);
            connect(m_cb_for_data[num_table][num_row], &QCheckBox::toggled,  ([this, num_table, num_row](bool is_toggled)
            {
                m_kia_settings->m_kia_gui_settings->m_status_for_table_state[num_table][num_row] = QString::number(is_toggled);
                emit send_state_and_num_row(num_table, num_row, is_toggled);
            }));
            m_table[num_table]->setCellWidget(num_row, IS_VISIBILYTY, m_cb_for_data[num_table][num_row]);



            m_cb_for_color[num_table][num_row]->hide();
            m_cb_for_color[num_table][num_row]->setChecked(true);
            connect(m_cb_for_color[num_table][num_row], &QCheckBox::toggled,  ([this, num_table, num_row](bool is_toggled)
            {
                m_kia_settings->m_kia_gui_settings->m_color_for_table_state[num_table][num_row] = QString::number(is_toggled);
                emit send_color_and_num_row(num_table, num_row, is_toggled);
            }));
            m_table[num_table]->setCellWidget(num_row, IS_COLOR, m_cb_for_color[num_table][num_row]);
        }

    }
    connect(ui->lw_name_table, &QListWidget::itemClicked, this, [this, rows_from_table](QListWidgetItem *item)
    {
        Q_UNUSED(item)
        for (uint16_t num_table = 0; num_table < m_table.size(); ++num_table)
        {
            if (num_table != ui->lw_name_table->currentRow())
                m_table[num_table]->hide();
        }
        m_table[ui->lw_name_table->currentRow()]->show();
        ui->gridLayout_3->addWidget(m_table[ui->lw_name_table->currentRow()], 1, 1);
    });

}

void Kia_options_interface::set_check_box_for_table_state(qint16 num_table, QStringList active_rows)
{
    m_status[num_table] = active_rows;
    for (uint16_t num_row = 0; num_row < active_rows.size(); ++num_row)
    {
        emit send_state_and_num_row(num_table, num_row, active_rows[num_row].toInt());
        if (m_status[num_table].size() != 0)
            m_cb_for_data[num_table][num_row]->setChecked(m_status[num_table][num_row].toInt());
    }
}

void Kia_options_interface::set_check_box_for_table_state_color(qint16 num_table, QStringList active_rows)
{
    m_color[num_table] = active_rows;
    for (uint16_t num_row = 0; num_row < active_rows.size(); ++num_row)
    {
        emit send_color_and_num_row(num_table, num_row, active_rows[num_row].toInt());
        if (m_color[num_table].size() != 0)
            m_cb_for_color[num_table][num_row]->setChecked(m_color[num_table][num_row].toInt());
    }
}
