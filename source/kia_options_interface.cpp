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

void Kia_options_interface::create_actions_menu_settings(std::vector<std::pair<QString, QList<QAction *> > > actions)
{
    m_cb_for_actions.resize(actions.size());
    m_actions_settings = new QTabWidget(this);
    m_actions_settings->setTabPosition(QTabWidget::South);
    ui->gridLayout_2->addWidget(m_actions_settings);
    std::vector<QWidget*> widgets;
    std::vector<QHBoxLayout*> layouts;
    m_kia_settings->m_kia_gui_settings->m_status_for_menu_action.resize(actions.size());
    m_menu_actions.resize(actions.size());
    for (uint16_t num_menu = 0; num_menu < actions.size(); ++num_menu)
    {

        widgets.push_back(new QWidget(this));
        layouts.push_back(new QHBoxLayout(widgets[num_menu]));
        m_lw_for_actions.push_back(new QListWidget(this));
        layouts[num_menu]->addWidget(m_lw_for_actions[num_menu]);
        for (uint16_t num_action = 0; num_action < actions[num_menu].second.size(); num_action++)
        {
            m_menu_actions[num_menu].push_back(actions[num_menu].second[num_action]->text());
            m_kia_settings->m_kia_gui_settings->m_status_for_menu_action[num_menu].push_back("1");
            m_cb_for_actions[num_menu].push_back(new QCheckBox(actions[num_menu].second[num_action]->text(), this));
            m_cb_for_actions[num_menu][num_action]->setChecked(true);
            if (!actions[num_menu].second[num_action]->text().isEmpty())
            {
                m_lw_for_actions[num_menu]->setItemWidget(new QListWidgetItem(m_lw_for_actions[num_menu]), m_cb_for_actions[num_menu][num_action]);
                connect(m_cb_for_actions[num_menu][num_action], &QCheckBox::toggled,  ([this, num_menu, num_action](bool is_toggled)
                {
                    m_kia_settings->m_kia_gui_settings->m_status_for_menu_action[num_menu][num_action] = QString::number(is_toggled);
                    emit send_num_actions(num_menu, num_action, is_toggled);
                }));
            }
            else
            {
                m_cb_for_actions[num_menu][num_action]->setVisible(false);
            }
        }
        m_actions_settings->addTab(widgets[num_menu], actions[num_menu].first);
    }
}

void Kia_options_interface::create_menu_for_menu_bar(std::vector<QMenu*> menu_list)
{
    m_cb_for_menu.resize(menu_list.size());
    for (uint16_t num_menu = 0; num_menu < menu_list.size(); ++num_menu)
    {
        m_cb_for_menu[num_menu] = new QCheckBox(menu_list[num_menu]->title(), this);
        m_cb_for_menu[num_menu]->setChecked(true);
        ui->gridLayout_4->addWidget(m_cb_for_menu[num_menu]);
        m_kia_settings->m_kia_gui_settings->m_status_menu_from_menubar.push_back("1");
        connect(m_cb_for_menu[num_menu], &QCheckBox::toggled,  ([this, num_menu](bool is_toggled)
        {
            m_kia_settings->m_kia_gui_settings->m_status_menu_from_menubar[num_menu] = QString::number(is_toggled);
            emit send_num_menus(num_menu, is_toggled);
        }));
    }
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

void Kia_options_interface::set_list_for_menu_actions(qint16 num_menu, QStringList list_actions)
{
    if (list_actions.size() == m_menu_actions[num_menu].size())
    {
        m_menu_actions[num_menu] = list_actions;
        for (uint16_t num_action = 0; num_action < list_actions.size(); ++num_action)
        {
            emit send_num_actions(num_menu, num_action, list_actions[num_action].toInt());
            if (m_menu_actions[num_menu].size() != 0)
                m_cb_for_actions[num_menu][num_action]->setChecked(m_menu_actions[num_menu][num_action].toInt());
        }
    }
}

void Kia_options_interface::set_list_for_menu_actions_for_menubar(QStringList list_actions)
{
    if (list_actions.size() == m_cb_for_menu.size())
    {
        for (uint16_t num_menu = 0; num_menu < list_actions.size(); ++num_menu)
        {
            emit send_num_menus(num_menu, list_actions[num_menu].toInt());
            m_cb_for_menu[num_menu]->setChecked(list_actions[num_menu].toInt());
        }
    }
}
