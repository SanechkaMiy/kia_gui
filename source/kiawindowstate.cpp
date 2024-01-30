#include "kiawindowstate.h"
#include "ui_kiawindowstate.h"
#include "unistd.h"
KiaWindowState::KiaWindowState(std::shared_ptr<Kia_settings> kia_settings, QWidget *parent) :
    QDialog(parent)
  , m_kia_settings(kia_settings)
  , ui(new Ui::KiaWindowState)
{
    ui->setupUi(this);

    m_layout_for_place_table_state = new QHBoxLayout(this);
    m_set_table = new QTableWidget(this);
    m_layout_for_place_table_state->addWidget(m_set_table);
    installEventFilter(parent);

}

KiaWindowState::~KiaWindowState()
{
    delete ui;
}

void KiaWindowState::table_setup(qint16 type_bi)
{
    m_set_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    m_set_table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_set_table->setColumnCount(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_set_table->setRowCount(m_kia_settings->m_kia_bi_settings->m_bi_row_name[type_bi].size());
    m_line_edit_data_into_table.resize(m_kia_settings->m_kia_bi_settings->m_bi_row_name[type_bi].size());
    m_true_color.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_count_for_change_color.resize( m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_is_color.resize(m_kia_settings->m_kia_bi_settings->m_bi_row_name[type_bi].size());
    for (int i = 0; i < m_kia_settings->m_kia_bi_settings->m_bi_row_name[type_bi].size(); ++i)
    {
        auto item_vertical_header = new QTableWidgetItem(m_kia_settings->m_kia_bi_settings->m_bi_row_name[type_bi][i]);
        m_set_table->setVerticalHeaderItem(i, item_vertical_header);
        item_vertical_header->setTextAlignment(Qt::AlignCenter);
    }
    for (int coll = 0; coll <  m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++coll)
    {
        auto num_dev = QString::number((coll % 2) + 1);
        m_set_table->setHorizontalHeaderItem(coll, new QTableWidgetItem("Прибор " + num_dev));
        for (int row = 0; row < m_kia_settings->m_kia_bi_settings->m_bi_row_name[type_bi].size(); ++row)
        {
            m_line_edit_data_into_table[coll].push_back(new QLineEdit());
            m_line_edit_data_into_table[coll][row]->setReadOnly(true);
            m_set_table->setCellWidget(row, coll, m_line_edit_data_into_table[coll][row]);
        }
    }

}

QStringList KiaWindowState::get_row()
{
    QStringList ret_rows;
    for (uint16_t num_row = 0; num_row < m_set_table->rowCount(); ++num_row)
        ret_rows.push_back(m_set_table->verticalHeaderItem(num_row)->text());
    return ret_rows;
}

void KiaWindowState::hide_or_show_row(qint16 index_row, bool state)
{
    if (!state)
        m_set_table->hideRow(index_row);
    else
        m_set_table->showRow(index_row);
}

void KiaWindowState::set_color_row(qint16 index_row, bool state)
{
    if (!state)
        m_is_color[index_row] = true;
    else
        m_is_color[index_row] = false;
}

void KiaWindowState::set_width_for_vertical_header(qint16 width_header, qint16 width_col)
{
    m_set_table->verticalHeader()->setFixedWidth(width_header);
    for (int coll = 0; coll < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++coll)
    {
        m_set_table->setColumnWidth(coll, width_col);
    }
}

void KiaWindowState::set_data_to_table_state(qint16 type_bi, QStringList data_from_server)
{
    Qt::GlobalColor color;
    QString str_status;
    QPalette pallete_status_on;
    pallete_status_on.setColor(QPalette::Base, Qt::green);

    QPalette pallete_status_cold;
    pallete_status_cold.setColor(QPalette::Base, Qt::blue);

    QPalette pallete_status_off;
    pallete_status_off.setColor(QPalette::Base, Qt::red);

    QPalette pallete_status_default;
    pallete_status_default.setColor(QPalette::Base, Qt::white);

    for (int row = 0; row < m_kia_settings->m_kia_bi_settings->m_bi_row_name[type_bi].size(); ++row)
    {
        auto col = data_from_server[1].toInt() + data_from_server[0].toInt() * m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi];

        if (row == Biu_1C)
        {
            switch (data_from_server[row + 2].toInt())
            {
            case BIS1M_BOTH_OFF:
                str_status = "-";
                color = Qt::red;
                break;
            case BIS1SM_MAIN_ON:
                str_status = "осн";
                color = Qt::blue;
                break;
            case BIS1SM_REZERV_ON:
                str_status = "рез";
                color = Qt::yellow;
                break;
            case BIS1SM_BOTH_ON:
                str_status = "осн+рез";
                color = Qt::green;
                break;
            }

        }
        else
            str_status = data_from_server[row + 2];

        m_line_edit_data_into_table[col][row]->setText(str_status);
        if (!m_is_color[row])
        {
            m_true_color[col] = color;
            if (row >= Biu_ST_KS && row  <= Biu_BTVK)
            {
                if (str_status == "есть")
                    m_line_edit_data_into_table[col][row]->setPalette(pallete_status_on);
                else
                    m_line_edit_data_into_table[col][row]->setPalette(pallete_status_off);
            }

            if (row == Biu_td)
            {
                if (str_status.toFloat() < 0)
                    m_line_edit_data_into_table[col][row]->setPalette(pallete_status_cold);
                else if ( (str_status.toFloat() <= 30))
                    m_line_edit_data_into_table[col][row]->setPalette(pallete_status_on);
                else
                    m_line_edit_data_into_table[col][row]->setPalette(pallete_status_off);
                if (str_status == "---")
                    m_line_edit_data_into_table[col][row]->setPalette(pallete_status_default);
            }
        }
        else
            m_line_edit_data_into_table[col][row]->setPalette(pallete_status_default);
    }

}

void KiaWindowState::set_status_bi_1s_mark(qint16 num_bi)
{
    if (!m_is_color[Biu_1C])
    {
        auto current_color = Qt::white;
        for (int coll = 0; coll < m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi]; ++coll)
        {
            auto cur_col = coll + num_bi * m_kia_settings->m_kia_bi_settings->m_bi_count_channel[m_kia_settings->m_type_bi];
            m_count_for_change_color[cur_col] = (m_count_for_change_color[cur_col] + 1)  % 2;
            if (m_count_for_change_color[cur_col]  == CS_IS_ON)
                current_color = Qt::white;
            else
                current_color = m_true_color[cur_col];
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Base, current_color);
            m_line_edit_data_into_table[cur_col][Biu_1C]->setPalette(*palette);
        }
    }
}
