#include "kia_debug_commands.h"
#include "ui_kia_debug_commands.h"

Kia_debug_commands::Kia_debug_commands(std::shared_ptr<Kia_settings> kia_settings, std::shared_ptr<Client> client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kia_debug_commands)
  , m_kia_settings(kia_settings)
  , m_client(client)
{
    ui->setupUi(this);
    const uint16_t max_count_item = 33;
    const uint16_t max_visible_item = 5;

    for(uint16_t item = 0; item < max_count_item; ++item)
    {
        if (item < m_struct_commands.m_count_direction)
            ui->cb_direction->addItem(QString::number(item));
        if (item < m_struct_commands.m_count_format)
            ui->cb_format->addItem(QString::number(item));
        if (item >= 1 && item < m_struct_commands.m_count_sub_address)
            ui->cb_sub_address->addItem(QString::number(item));
        if (item >= 1 && item <= m_struct_commands.m_count_word_data)
            ui->cb_word_data->addItem(QString::number(item));
    }
    ui->cb_direction->setCurrentIndex(1);

    ui->cb_format->setEditable(true);
    ui->cb_sub_address->setEditable(true);
    ui->cb_word_data->setEditable(true);

    ui->cb_format->setMaxVisibleItems(max_visible_item);
    ui->cb_sub_address->setMaxVisibleItems(max_visible_item);
    ui->cb_word_data->setMaxVisibleItems(max_visible_item);
    connect(ui->lw_commands, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item)
    {
        Q_UNUSED(item)
        m_client->send_data_to_server(DEBUGGING_COMMAND, m_kia_settings->m_kia_gui_settings->m_debug_comand_param[ui->lw_commands->currentRow()]);
    });

    ui->tw_for_sd->hide();
    ui->tw_for_sd->setColumnCount(1);
    ui->tw_for_sd->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_for_sd->setHorizontalHeaderItem(0, new QTableWidgetItem("СД"));
    //ui->tw_for_sd->setRowCount(32);
}

Kia_debug_commands::~Kia_debug_commands()
{
    delete ui;
}

void Kia_debug_commands::on_add_command_clicked()
{
    add_command();
}

void Kia_debug_commands::add_command()
{
    ui->lw_commands->addItem(ui->le_struct_id_desc->text());
    for (int num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
        {
            QStringList debug_command;
            debug_command.push_back(QString::number(num_bokz));
            debug_command.push_back(ui->cb_direction->currentText());
            debug_command.push_back(ui->cb_format->currentText());
            debug_command.push_back(ui->cb_sub_address->currentText());
            debug_command.push_back(ui->cb_word_data->currentText());
            debug_command.push_back(ui->le_struct_id->text());
            debug_command.push_back(ui->le_struct_id_desc->text());
            if (ui->cb_direction == 0)
            {
                for (uint16_t num_word = 0; num_word < ui->cb_word_data->currentText().toInt(); ++num_word)
                {
                    debug_command.push_back(ui->tw_for_sd->takeItem(num_word,1)->text());
                }

            }
            m_kia_settings->m_kia_gui_settings->m_debug_comand_param.push_back(debug_command);
            //m_kia_settings->m
        }
    }
}


void Kia_debug_commands::on_delete_command_clicked()
{
    if (ui->lw_commands->count() != 0)
    {
        m_kia_settings->m_kia_gui_settings->m_debug_comand_param.erase(m_kia_settings->m_kia_gui_settings->m_debug_comand_param.begin() + ui->lw_commands->currentRow());
        delete ui->lw_commands->currentItem();
    }
}


void Kia_debug_commands::on_cb_direction_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->tw_for_sd->show();
    }
    else
    {
        ui->tw_for_sd->hide();
    }
}


void Kia_debug_commands::on_cb_word_data_currentIndexChanged(const QString &arg1)
{
    ui->tw_for_sd->setRowCount(arg1.toInt());
}

