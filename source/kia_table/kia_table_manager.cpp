#include "kia_table_manager.h"

Kia_table_manager::Kia_table_manager(std::shared_ptr<Kia_settings> kia_settings,
                                     std::shared_ptr<Kia_constructor> kia_constructor,
                                     QWidget *parent)
    : m_parent(parent),
      m_kia_settings(kia_settings),
      m_kia_constructor(kia_constructor)
{
    init_table_manager();
    connect(m_kia_constructor.get(), SIGNAL(add_table(QStringList, QStringList)), this, SLOT(create_table_slot(QStringList, QStringList)));
    connect(m_kia_constructor.get(), SIGNAL(remove_table(qint16)), this, SLOT(remove_table_slot(qint16)));
    connect(m_kia_constructor.get(), SIGNAL(show_table(int32_t)), this, SLOT(show_tables(int32_t)));
}

QVector<QDialog *> Kia_table_manager::get_table_widget()
{
    QVector<QDialog*> list_widget;
    for (auto el : m_kia_custom_dialog)
        list_widget.push_back(el);
    return list_widget;
}

Kia_table_manager::~Kia_table_manager()
{
    std::cout << "desctr table_manager" << std::endl;
}

void Kia_table_manager::create_table_slot(QStringList query_param, QStringList data)
{
    m_num_table++;
    m_kia_custom_dialog.push_back(new Kia_custom_dialog(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[query_param[QP_NUM_MAIN_TAB_WIDGET].toInt()]));
    m_dialog.push_back(new QDialog());
    m_l_for_tables.push_back(new QVBoxLayout(m_dialog[m_num_table]));
    m_kias_data_from_db.push_back(std::make_shared<Kias_data_from_db>());
    m_kia_db.push_back(std::make_shared<Kia_db>("con_table_" + QString::number(m_num_table), m_kia_settings, m_kias_data_from_db[m_num_table]));
    m_kia_db[m_num_table]->set_query(query_param, data);
    m_kia_tables.push_back(new Kia_tables(m_kia_db[m_num_table], m_kia_settings, m_kias_data_from_db[m_num_table]));
    connect(m_kia_tables[m_num_table], SIGNAL(set_default_pos()), m_kia_custom_dialog[m_num_table], SLOT(set_default_pos_slot()));
    m_l_for_tables[m_num_table]->addWidget(m_kia_tables[m_num_table]);
    m_kia_custom_dialog[m_num_table]->set_wiget_to_layout(m_kia_tables[m_num_table]);
    start_data_timer(m_num_table);
    m_kia_constructor->add_table_to_list(query_param);
    m_dialog[m_num_table]->setWindowTitle("Таблица " + query_param[QP_TYPE_ARR] +" №" + QString::number(query_param[QP_NUM_WIDGET].toInt() + 1)
                                          + " " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
                               + " " + QString::number(query_param[QP_NUM_BOKZ].toInt() + 1));

    emit create_action("Таблица " + query_param[QP_TYPE_ARR] +" №" + QString::number(query_param[QP_NUM_WIDGET].toInt() + 1)
                       + " " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
            + " " + QString::number(query_param[QP_NUM_BOKZ].toInt() + 1), m_num_table);
}

void Kia_table_manager::remove_table_slot(qint16 num_table)
{
    disconnect(m_kia_tables[num_table], SIGNAL(set_default_pos()), m_kia_custom_dialog[num_table], SLOT(set_wiget_to_layout()));
    delete m_kia_tables[num_table];
    m_kia_db[num_table].reset();
    m_kias_data_from_db[num_table].reset();
    delete m_l_for_tables[num_table];
    delete m_dialog[num_table];
    delete m_kia_custom_dialog[num_table];
    m_kia_tables.erase(m_kia_tables.begin() + num_table);
    m_kia_db.erase(m_kia_db.begin() + num_table);
    m_kias_data_from_db.erase(m_kias_data_from_db.begin() + num_table);
    m_l_for_tables.erase(m_l_for_tables.begin() + num_table);
    m_dialog.erase(m_dialog.begin() + num_table);
    m_kia_custom_dialog.erase(m_kia_custom_dialog.begin() + num_table);
    m_num_table -= 1;
    emit remove_action(num_table);
}

void Kia_table_manager::show_tables(int32_t num_table)
{
    m_kia_custom_dialog[num_table]->show();
    m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[num_table]] = m_kia_custom_dialog[num_table]->isVisible();
}

void Kia_table_manager::init_table_manager()
{
    m_timer = std::make_shared<QTimer>();
    m_timer->start(0);
}

void Kia_table_manager::start_data_timer(int32_t &num_table)
{
    connect(m_timer.get(), SIGNAL(timeout()), m_kia_tables[num_table], SLOT(get_data_from_db_slot()));
}
