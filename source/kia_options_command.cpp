#include "kia_options_command.h"
#include "ui_kia_options_command.h"

Kia_options_command::Kia_options_command(std::shared_ptr<Kia_settings> kia_settings, std::shared_ptr<Client> client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kia_options_command)
  , m_kia_settings(kia_settings)
  , m_client(client)
{
    ui->setupUi(this);
    create_template_for_table();
    m_layout_for_all_widget = new QGridLayout(this);
    m_layout_for_button = new QGridLayout();
    m_layout_for_button->addWidget(ui->load_param, 0, 0);
    m_layout_for_button->addWidget(ui->save_param, 1, 0);
    m_layout_for_button->addWidget(ui->set_param, 0, 1);
    m_layout_for_button->addWidget(ui->get_param, 1, 1);
    m_layout_for_all_widget->addLayout(m_layout_for_button, 1, 0);
    m_command_settings = new QTabWidget(this);
    m_wgt.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_widgets.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_status_changed_edit.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_status_changed_table.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_lb_name_command.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_le_edit_command.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_tables.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        m_tab_for_type_command.push_back(new QTabWidget(this));
        m_tab_for_type_command[num_bokz]->setTabPosition(QTabWidget::South);
        m_command_settings->addTab(m_tab_for_type_command[num_bokz], "");
        QTabBar *tabbar = m_command_settings->tabBar();
        m_command_settings->setTabPosition(QTabWidget::East);

        tabbar->setTabButton(num_bokz, QTabBar::RightSide, new QLabel("БОКЗ №" + QString::number(num_bokz + 1)));
        //m_layout_for_place_options_tab_widget.push_back(new QVBoxLayout(kia_options_list[num_widget]));
        m_wgt[num_bokz].push_back(new QWidget(this));
        m_wgt[num_bokz].push_back(new QWidget(this));
        m_wgt[num_bokz].push_back(new QWidget(this));
        m_widgets[num_bokz].push_back(std::make_tuple(m_wgt[num_bokz][IS_PARAM], new QGridLayout(m_wgt[num_bokz][IS_PARAM]), "Параметры"));
        m_widgets[num_bokz].push_back(std::make_tuple(m_wgt[num_bokz][IS_TABLE], new QGridLayout(m_wgt[num_bokz][IS_TABLE]), "Таблицы"));
        for (auto& el : m_widgets[num_bokz])
            m_tab_for_type_command[num_bokz]->addTab(std::get<0>(el), std::get<2>(el));
        for (auto el : m_kia_settings->m_kia_gui_settings->m_commands_to_pn)
        {
            switch(std::get<TP_TYPE_VIEW>(el))
            {
            case IS_PARAM:
                add_edit(num_bokz, std::get<TP_NAME>(el), std::get<TP_KEY>(el),
                         std::get<TP_TYPE_COMMAND>(el));
                break;
            case IS_TABLE:
                add_table(num_bokz, m_dict_for_table_size[std::get<TP_KEY>(el)][0],
                        m_dict_for_table_size[std::get<TP_KEY>(el)][1],
                        std::get<TP_NAME>(el), std::get<TP_KEY>(el), std::get<TP_TYPE_COMMAND>(el));
                break;
            }
        }
        for (uint16_t num_edit = 0; num_edit < m_status_changed_edit[num_bokz].size(); ++num_edit)
        {
            connect(m_le_edit_command[num_bokz][m_status_changed_edit[num_bokz][num_edit].second], &QLineEdit::textChanged, [this, num_edit, num_bokz](const QString & is_changed)
            {
                Q_UNUSED(is_changed)
                m_status_changed_edit[num_bokz][num_edit].first = IS_CHANGED;
                QPalette palette;
                palette.setColor(QPalette::Base, Qt::red);
                m_le_edit_command[num_bokz][m_status_changed_edit[num_bokz][num_edit].second]->setPalette(palette);

            });
        }

        for (uint16_t num_table = 0; num_table < m_status_changed_table[num_bokz].size(); ++num_table)
        {
            connect(m_tables[num_bokz][m_status_changed_table[num_bokz][num_table].second], &QTableWidget::itemChanged, [this, num_table, num_bokz](QTableWidgetItem *item)
            {
                Q_UNUSED(item)
                m_status_changed_table[num_bokz][num_table].first = IS_CHANGED;
                QPalette palette;
                palette.setColor(QPalette::Base, Qt::red);
                m_tables[num_bokz][m_status_changed_table[num_bokz][num_table].second]->setPalette(palette);

            });
        }
    }
    m_layout_for_all_widget->addWidget(m_command_settings, 0, 0);

}

Kia_options_command::~Kia_options_command()
{
    delete ui;
}

void Kia_options_command::on_set_param_clicked()
{
    QPalette palette;
    palette.setColor(QPalette::Base, Qt::white);
    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        for (uint16_t num_edit = 0; num_edit < m_status_changed_edit[num_bokz].size(); ++num_edit)
        {
            if (m_status_changed_edit[num_bokz][num_edit].first == IS_CHANGED)
            {
                m_le_edit_command[num_bokz][m_status_changed_edit[num_bokz][num_edit].second]->setPalette(palette);
                QStringList param_list;
                param_list.push_back(QString::number(m_status_changed_edit[num_bokz][num_edit].second));
                param_list.push_back(m_le_edit_command[num_bokz][m_status_changed_edit[num_bokz][num_edit].second]->text());
                m_client->send_data_to_server(SET_UPN, param_list);
                m_status_changed_edit[num_bokz][num_edit].first = IS_DEFAULT;
            }
        }

        for (uint16_t num_table = 0; num_table < m_status_changed_table[num_bokz].size(); ++num_table)
        {
            if (m_status_changed_table[num_bokz][num_table].first == IS_CHANGED)
            {
                m_tables[num_bokz][m_status_changed_table[num_bokz][num_table].second]->setPalette(palette);
                QStringList param_list;
                param_list.push_back(QString::number(m_status_changed_table[num_bokz][num_table].second));
                for (uint16_t row = 0; row < m_tables[num_bokz][m_status_changed_table[num_bokz][num_table].second]->rowCount(); ++row)
                {
                    for (uint16_t col = 0; col < m_tables[num_bokz][m_status_changed_table[num_bokz][num_table].second]->columnCount(); ++col)
                    {
                        param_list.push_back(m_tables[num_bokz][m_status_changed_table[num_bokz][num_table].second]->item(row, col)->text());
                    }
                }
                m_client->send_data_to_server(SET_UPN, param_list);
                m_status_changed_table[num_bokz][num_table].first = IS_DEFAULT;
            }
        }

    }
}


void Kia_options_command::on_get_param_clicked()
{
    QStringList param_list;
    for (auto el : m_kia_settings->m_kia_gui_settings->m_commands_to_pn)
    {
        param_list.push_back(QString::number(std::get<TP_TYPE_COMMAND>(el)));
    }
    m_client->send_data_to_server(GET_CHPN, param_list);
}

void Kia_options_command::set_read_command(qint16 num_bokz, qint16 type_data, qint16 type_command, QStringList data)
{
    QPalette palette;
    palette.setColor(QPalette::Base, Qt::white);

    switch(type_data)
    {
    case IS_PARAM:
        for (auto el : data)
            m_le_edit_command[num_bokz][type_command]->setText(el);
        m_le_edit_command[num_bokz][type_command]->setPalette(palette);
        m_status_changed_edit[num_bokz][type_command].first = IS_DEFAULT;
        break;
    case IS_TABLE:
        for (uint16_t row = 0; row < m_tables[num_bokz][type_command]->rowCount(); row++)
        {
            for (uint16_t coll = 0; coll < m_tables[num_bokz][type_command]->columnCount(); coll++)
            {
                m_tables[num_bokz][type_command]->setItem(row, coll, new QTableWidgetItem(data[coll + row * m_tables[num_bokz][type_command]->columnCount()]));
            }
        }
        break;
    }

}

void Kia_options_command::add_edit(uint16_t num_bokz, const QString &name_param, const QString &key, const uint16_t &name_to_send)
{
    auto pair = std::make_pair(IS_DEFAULT, name_to_send);
    m_status_changed_edit[num_bokz].push_back(pair);
    m_lb_name_command[num_bokz][name_to_send] = new QLabel(name_param, this);
    m_le_edit_command[num_bokz][name_to_send] = new QLineEdit(this);
    m_dict_type_command_for_load[key + "_" + QString::number(num_bokz)] = name_to_send;
    std::get<1>(m_widgets[num_bokz][IS_PARAM])->addWidget(m_lb_name_command[num_bokz][name_to_send], name_to_send, 0);
    std::get<1>(m_widgets[num_bokz][IS_PARAM])->addWidget(m_le_edit_command[num_bokz][name_to_send], name_to_send, 1);
}

void Kia_options_command::add_table(uint16_t num_bokz, uint16_t row, uint16_t collumn, const QString &name_param, const QString &key, const uint16_t &name_to_send)
{
    auto pair = std::make_pair(IS_DEFAULT, name_to_send);
    m_status_changed_table[num_bokz].push_back(pair);
    m_lb_name_command[num_bokz][name_to_send] = new QLabel(name_param, this);
    m_tables[num_bokz][name_to_send] = new QTableWidget(row, collumn, this);
    m_tables[num_bokz][name_to_send]->horizontalHeader()->setHidden(true);
    m_tables[num_bokz][name_to_send]->verticalHeader()->setHidden(true);
    m_tables[num_bokz][name_to_send]->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tables[num_bokz][name_to_send]->horizontalHeader()->setStretchLastSection(true);
    m_tables[num_bokz][name_to_send]->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tables[num_bokz][name_to_send]->verticalHeader()->setStretchLastSection(true);
    //m_tables[num_bokz][name_to_send]->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_dict_type_command_for_load[key + "_" + QString::number(num_bokz)] = name_to_send;
    for (uint16_t row = 0; row < m_tables[num_bokz][name_to_send]->rowCount(); ++row)
        for (uint16_t col = 0; col < m_tables[num_bokz][name_to_send]->columnCount(); ++col)
        {
            m_tables[num_bokz][name_to_send]->setItem(row, col, new QTableWidgetItem("0"));
        }
    std::get<1>(m_widgets[num_bokz][IS_TABLE])->addWidget(m_lb_name_command[num_bokz][name_to_send], name_to_send, 0);
    std::get<1>(m_widgets[num_bokz][IS_TABLE])->addWidget(m_tables[num_bokz][name_to_send], name_to_send, 1);

}

void Kia_options_command::create_template_for_table()
{
    std::array<uint16_t, 2> mat = {3, 3};
    m_dict_for_table_size["mat_psk"] = mat;

    std::array<uint16_t, 2> qa = {4, 1};
    m_dict_for_table_size["qo"] = qa;

    std::array<uint16_t, 2> w = {3, 1};
    m_dict_for_table_size["wo"] = w;

    std::array<uint16_t, 2> kd = {2, 14};
    m_dict_for_table_size["kd"] = kd;
}


void Kia_options_command::on_load_param_clicked()
{
    std::ifstream f("../source/Kia_resources/kia_load_command_param.json", std::ifstream::in);
    json j;
    f >> j;
    uint16_t ind = 0;
    for (auto& el : j["params"].items())
    {
        m_le_edit_command[m_command_settings->currentIndex()][m_dict_type_command_for_load[QString::fromStdString(el.key())
                + "_" + QString::number(m_command_settings->currentIndex())]]->setText(QString::fromStdString(el.value().dump()));
    }
    for (auto& el : j["tables"].items())
    {
        if (!el.value().empty())
        {
            for (uint16_t num_el = 0; num_el < el.value().size(); ++num_el)
            {
                if (el.value()[num_el].size() == 1)
                {
                    m_tables[m_command_settings->currentIndex()][m_dict_type_command_for_load[QString::fromStdString(el.key())
                            + "_" + QString::number(m_command_settings->currentIndex())]]->setItem(num_el, el.value()[num_el].size() - 1,
                                                                                                   new QTableWidgetItem(QString::fromStdString(el.value()[num_el].dump())));
                }
                else
                {
                    for (uint16_t num = 0; num < el.value()[num_el].size(); ++num)
                    {
                        m_tables[m_command_settings->currentIndex()][m_dict_type_command_for_load[QString::fromStdString(el.key())
                                + "_" + QString::number(m_command_settings->currentIndex())]]->setItem(num_el, num,
                                                                                                       new QTableWidgetItem(QString::fromStdString(el.value()[num_el][num].dump())));
                    }
                }
            }

        }
        ind++;
    }
}

