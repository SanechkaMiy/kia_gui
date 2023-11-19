#include "kia_tables.h"

Kia_tables::Kia_tables(std::shared_ptr<Kia_db> kia_db,
                       std::shared_ptr<Kia_settings> kia_settings,
                       std::shared_ptr<Kias_data_from_db> kias_graph_data,
                       QWidget *parent) :
    QTableView(parent),
    m_kia_db(kia_db),
    m_kia_settings(kia_settings),
    m_kias_graph_data(kias_graph_data)
{
    connect(this, SIGNAL(get_data_from_db(QString, QString)), m_kia_db.get(), SLOT(get_data_from_db_for_table_slot(QString, QString)));
    connect(this, SIGNAL(send_data_on_table()), this, SLOT(set_data_on_table_slot()));
}

void Kia_tables::get_data_from_db_slot()
{
    start_get_data = std::async([this]()
    {
        if (m_kia_settings->m_kias_db->m_key <= last_point_key)
            last_point_key = m_kia_settings->m_kias_db->m_key;
        if (m_kia_settings->m_kias_db->m_key - last_point_key >= 1)
        {
            emit get_data_from_db(m_kia_settings->m_kias_db->m_begin.toString("hh:mm:ss.zzz"),
                                  m_kia_settings->m_kias_db->m_end.toString("hh:mm:ss.zzz"));
            emit send_data_on_table();
            last_point_key = m_kia_settings->m_kias_db->m_key;
        }
    });
}

void Kia_tables::set_data_on_table_slot()
{
    setModel(m_kias_graph_data->m_model.front());
    m_kias_graph_data->m_model.pop();

}
