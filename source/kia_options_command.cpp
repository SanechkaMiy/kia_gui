#include "kia_options_command.h"
#include "ui_kia_options_command.h"

Kia_options_command::Kia_options_command(std::shared_ptr<Kia_settings> kia_settings, std::shared_ptr<Client> client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kia_options_command)
  , m_kia_settings(kia_settings)
  , m_client(client)
{
    ui->setupUi(this);
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
    m_edit_count.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
    m_table_count.resize(m_kia_settings->m_kia_bokz_settings->m_count_bokz);
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
        add_edit(num_bokz, "Допуск распознования", "epsilon", SET_EPSILON);
        add_edit(num_bokz, "Фокус", "focus", SET_FOCUS);
        add_edit(num_bokz, "Время эксопонирования", "texp", SET_TEXP);
        add_edit(num_bokz, "Координата X", "cord_x", SET_CORD_X);
        add_edit(num_bokz, "Координата Y", "cord_y", SET_CORD_Y);

        add_table(num_bokz, 3, 3, "Матрица ПСК", "mat_psk", SET_MATRIX_PSK);
        add_table(num_bokz, 4, 1, "Qo", "qo", SET_QA);
        add_table(num_bokz, 3, 1, "Wo", "wo", SET_W);
        for (uint16_t num_edit = 0; num_edit < m_le_edit_command[num_bokz].size(); ++num_edit)
        {
            connect(m_le_edit_command[num_bokz][num_edit], &QLineEdit::textChanged, [this, num_edit, num_bokz](const QString & is_changed)
            {
                Q_UNUSED(is_changed)
                m_status_changed_edit[num_bokz][num_edit].first = IS_CHANGED;
                QPalette palette;
                palette.setColor(QPalette::Base, Qt::red);
                m_le_edit_command[num_bokz][num_edit]->setPalette(palette);

            });
        }

        for (uint16_t num_table = 0; num_table < m_tables[num_bokz].size(); ++num_table)
        {
            connect(m_tables[num_bokz][num_table], &QTableWidget::itemChanged, [this, num_table, num_bokz](QTableWidgetItem *item)
            {
                Q_UNUSED(item)
                m_status_changed_table[num_bokz][num_table].first = IS_CHANGED;
                QPalette palette;
                palette.setColor(QPalette::Base, Qt::red);
                m_tables[num_bokz][num_table]->setPalette(palette);

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
        for (uint16_t num_edit = 0; num_edit < m_le_edit_command[num_bokz].size(); ++num_edit)
        {
            if (m_status_changed_edit[num_bokz][num_edit].first == IS_CHANGED)
            {
                m_le_edit_command[num_bokz][num_edit]->setPalette(palette);
                QStringList param_list;
                param_list.push_back(QString::number(num_bokz));
                param_list.push_back(m_le_edit_command[num_bokz][num_edit]->text());
                m_client->send_data_to_server(m_status_changed_edit[num_bokz][num_edit].second, param_list);
                m_status_changed_edit[num_bokz][num_edit].first = IS_DEFAULT;
            }
        }

        for (uint16_t num_table = 0; num_table < m_tables[num_bokz].size(); ++num_table)
        {
            if (m_status_changed_table[num_bokz][num_table].first == IS_CHANGED)
            {
                m_tables[num_bokz][num_table]->setPalette(palette);
                QStringList param_list;
                param_list.push_back(QString::number(num_bokz));
                for (uint16_t row = 0; row < m_tables[num_bokz][num_table]->rowCount(); ++row)
                {
                    for (uint16_t col = 0; col < m_tables[num_bokz][num_table]->columnCount(); ++col)
                    {
                        param_list.push_back(m_tables[num_bokz][num_table]->item(row, col)->text());
                    }
                }
                m_client->send_data_to_server(m_status_changed_table[num_bokz][num_table].second, param_list);
                m_status_changed_table[num_bokz][num_table].first = IS_DEFAULT;
            }
        }
    }
}


void Kia_options_command::on_get_param_clicked()
{
    QStringList param_list;
    m_client->send_data_to_server(GET_EPSILON, param_list);
    m_client->send_data_to_server(GET_FOCUS, param_list);
    m_client->send_data_to_server(GET_TEXP, param_list);
}

void Kia_options_command::set_read_command(qint16 num_bokz, qint16 type_data, qint16 type_command, QString data)
{
    QPalette palette;
    palette.setColor(QPalette::Base, Qt::white);
    switch(type_data)
    {
    case IS_PARAM:
        m_le_edit_command[num_bokz][type_command]->setText(data);
        m_le_edit_command[num_bokz][type_command]->setPalette(palette);
        m_status_changed_edit[num_bokz][type_command].first = IS_DEFAULT;
        break;
    case IS_TABLE:
        //m_le_edit_command[num_bokz][type_command]->setText(data);
        break;
    }


}

void Kia_options_command::add_edit(uint16_t num_bokz, const QString &name_param, const QString &key, const uint16_t &name_to_send)
{
    auto pair = std::make_pair(IS_DEFAULT, name_to_send);
    m_status_changed_edit[num_bokz].push_back(pair);
    m_lb_name_command[num_bokz].push_back(new QLabel(name_param, this));
    m_le_edit_command[num_bokz].push_back(new QLineEdit(this));
    m_dict_type_command_for_load[key + "_" + QString::number(num_bokz)] = m_edit_count[num_bokz];
    std::get<1>(m_widgets[num_bokz][IS_PARAM])->addWidget(m_lb_name_command[num_bokz][m_edit_count[num_bokz]], m_edit_count[num_bokz], 0);
    std::get<1>(m_widgets[num_bokz][IS_PARAM])->addWidget(m_le_edit_command[num_bokz][m_edit_count[num_bokz]], m_edit_count[num_bokz], 1);
    m_edit_count[num_bokz]++;
}

void Kia_options_command::add_table(uint16_t num_bokz, uint16_t row, uint16_t collumn, const QString &name_param, const QString &key, const uint16_t &name_to_send)
{
    auto pair = std::make_pair(IS_DEFAULT, name_to_send);
    m_status_changed_table[num_bokz].push_back(pair);
    m_lb_name_command[num_bokz].push_back(new QLabel(name_param, this));
    m_tables[num_bokz].push_back(new QTableWidget(row, collumn, this));
    m_tables[num_bokz][m_table_count[num_bokz]]->horizontalHeader()->setHidden(true);
    m_tables[num_bokz][m_table_count[num_bokz]]->verticalHeader()->setHidden(true);
    m_tables[num_bokz][m_table_count[num_bokz]]->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tables[num_bokz][m_table_count[num_bokz]]->horizontalHeader()->setStretchLastSection(true);
    m_tables[num_bokz][m_table_count[num_bokz]]->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tables[num_bokz][m_table_count[num_bokz]]->verticalHeader()->setStretchLastSection(true);
    //m_tables[num_bokz][m_table_count[num_bokz]]->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_dict_type_command_for_load[key + "_" + QString::number(num_bokz)] = m_table_count[num_bokz];
    for (uint16_t row = 0; row < m_tables[num_bokz][m_table_count[num_bokz]]->rowCount(); ++row)
        for (uint16_t col = 0; col < m_tables[num_bokz][m_table_count[num_bokz]]->columnCount(); ++col)
        {
            m_tables[num_bokz][m_table_count[num_bokz]]->setItem(row, col, new QTableWidgetItem("0"));
        }
    std::get<1>(m_widgets[num_bokz][IS_TABLE])->addWidget(m_lb_name_command[num_bokz][m_edit_count[num_bokz]], m_table_count[num_bokz], 0);
    std::get<1>(m_widgets[num_bokz][IS_TABLE])->addWidget(m_tables[num_bokz][m_table_count[num_bokz]], m_table_count[num_bokz], 1);
    m_edit_count[num_bokz]++;
    m_table_count[num_bokz]++;
}


void Kia_options_command::on_load_param_clicked()
{
    std::ifstream f("kia_load_command_param.json", std::ifstream::in);
    json j;
    f >> j;
    uint16_t counter = 0;
    for (auto& el : j["params"].items())
    {
        m_le_edit_command[m_command_settings->currentIndex()][m_dict_type_command_for_load[QString::fromStdString(el.key())
                + "_" + QString::number(m_command_settings->currentIndex())]]->setText(QString::fromStdString(el.value().dump()));
    }
    for (auto& el : j["tables"].items())
    {
        if (!el.value().empty())
            std::cout << el.value()[2] << std::endl;
    }
    //    for (auto el : j["params"])
    //    {
    ////        std::string str = el;
    ////        std::cout << str << std::endl;
    //        std::cout <<  << std::endl;
    //        //std::cout << m_dict_type_command_for_load[QString::fromStdString(el) + "_" + QString::number(m_command_settings->currentIndex())] << std::endl;
    //        counter++;
    //    }
    counter = 0;
    for (auto el : j["tables"])
    {
        counter++;
    }
}

