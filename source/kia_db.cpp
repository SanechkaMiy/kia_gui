#include "kia_db.h"
#include <QDebug>
Kia_db::Kia_db(const QString &name_connection, std::shared_ptr<Kia_settings> kia_settings,
               std::shared_ptr<Kias_data_from_db> kias_data_from_db):
    m_kia_settings(kia_settings),
    m_kias_data_from_db(kias_data_from_db),
    m_name_connection(name_connection)
{
    create_connection(name_connection);
}

Kia_db::~Kia_db()
{
    m_db.close();
    QSqlDatabase::removeDatabase(m_name_connection);
    std::cout << "desctr db" << std::endl;
}

bool Kia_db::create_connection(const QString& name_connection)
{
    m_db = QSqlDatabase::addDatabase("QPSQL", name_connection);
    m_db.setHostName("127.0.0.1");
    m_db.setPort(5432);
    m_db.setDatabaseName("kia_bokzm60");
    m_db.setUserName("postgres");
    m_db.setPassword("88005553535");
    if (!m_db.open())
    {
        qDebug() << "cannot open data_base" << m_db.lastError();
        return false;
    }
    m_query = new QSqlQuery(m_db);
    return true;
}

void Kia_db::get_data_from_db_for_graph_slot(QString begin, QString end)
{
    m_kias_data_from_db->m_date_time_val.clear();
    m_kias_data_from_db->m_x_value.clear();
    m_kias_data_from_db->m_y_value.clear();
    m_kias_data_from_db->m_data_to_view.clear();
    QString data_get_db;
    QString data_get;
    if (m_query_param[QP_NUM_BOKZ_FOR_ANGLES].isEmpty())
    {

        if (m_query_param[QP_TYPE_ARR] == "frames")
        {
            data_get = "frame_name";
            data_get_db = ", " + data_get;
        }
        if (!m_query->exec("SELECT datetime, "+ m_query_param[QP_X] + ", " + m_query_param[QP_Y] + data_get_db + " FROM " + m_query_param[QP_TYPE_DEV] + "." + m_query_param[QP_TYPE_ARR] + " "
                           "WHERE host_id='04:92:26:d0:ef:d6'::macaddr "
                           "AND experiment_id='" + m_kia_settings->m_kias_db->m_experiment_id + "' AND serial_num=" + m_query_param[QP_NUM_BOKZ] + " "
                           "AND datetime >= '" + QDate::currentDate().toString("yyyy-MM-dd") + " " + begin + "' AND datetime <='" + QDate::currentDate().toString("yyyy-MM-dd") + " " + end + "';"))
        {
            qDebug() <<"Unable to execute query";
        }
        QSqlRecord rec = m_query->record();
        QDateTime date_time;
        QString data_to_view;
        double y_val;
        double x_val;
        while(m_query->next())
        {
            date_time = m_query->value(rec.indexOf("datetime")).toDateTime();
            y_val = m_query->value(rec.indexOf(m_query_param[QP_Y])).toDouble();
            x_val = m_query->value(rec.indexOf(m_query_param[QP_X])).toDouble();
            if (!data_get.isEmpty())
                data_to_view = m_query->value(rec.indexOf(data_get)).value<QString>();
            m_kias_data_from_db->m_date_time_val.push_back(date_time.time());
            m_kias_data_from_db->m_y_value.push_back(y_val);
            m_kias_data_from_db->m_x_value.push_back(x_val);
            m_kias_data_from_db->m_data_to_view.push_back(data_to_view);
        }

    }
    else
    {
        auto query_bokz_x = new QSqlQuery(m_db);
        if (!query_bokz_x->exec("SELECT datetime, "+ m_query_param[QP_X] + ", " + m_query_param[QP_Y] + data_get_db + " FROM " + m_query_param[QP_TYPE_DEV] + "." + m_query_param[QP_TYPE_ARR] + " "
                                "WHERE host_id='04:92:26:d0:ef:d6'::macaddr "
                                "AND experiment_id='" + m_kia_settings->m_kias_db->m_experiment_id + "' AND serial_num=" + m_query_param[QP_NUM_BOKZ] + " "
                                "AND datetime >= '" + QDate::currentDate().toString("yyyy-MM-dd") + " " + begin + "' AND datetime <='" + QDate::currentDate().toString("yyyy-MM-dd") + " " + end + "';"))
        {
            qDebug() <<"Unable to execute query";
        }
        QSqlRecord rec_x = query_bokz_x->record();
        double x_val;
        while(m_query->next())
        {
            x_val = m_query->value(rec_x.indexOf(m_query_param[QP_X])).toDouble();
            m_kias_data_from_db->m_x_value.push_back(x_val);
        }

        auto query_bokz_y = new QSqlQuery(m_db);
        if (!query_bokz_y->exec("SELECT datetime, "+ m_query_param[QP_X] + ", " + m_query_param[QP_Y] + data_get_db + " FROM " + m_query_param[QP_TYPE_DEV] + "." + m_query_param[QP_TYPE_ARR] + " "
                                "WHERE host_id='04:92:26:d0:ef:d6'::macaddr "
                                "AND experiment_id='" + m_kia_settings->m_kias_db->m_experiment_id + "' AND serial_num=" + m_query_param[QP_NUM_BOKZ_FOR_ANGLES] + " "
                                "AND datetime >= '" + QDate::currentDate().toString("yyyy-MM-dd") + " " + begin + "' AND datetime <='" + QDate::currentDate().toString("yyyy-MM-dd") + " " + end + "';"))
        {
            qDebug() <<"Unable to execute query";
        }
        QSqlRecord rec_y = query_bokz_y->record();
        double y_val;
        while(m_query->next())
        {
            y_val = m_query->value(rec_y.indexOf(m_query_param[QP_Y])).toDouble();
            m_kias_data_from_db->m_y_value.push_back(y_val);
        }
    }
}

void Kia_db::get_data_from_db_for_table_slot(QString begin, QString end)
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QString data;
    for (auto& el : m_data)
    {
        //std::cout << el.toStdString() << std::endl;
        if (!el.isEmpty())
        {
            if (el == "datetime")
                el = "datetime::text";
            if (el == "st1")
                el = "public.hex_literal(st1, 4) AS st1 ";
            if (el == "st2")
                el = "public.hex_literal(st2, 4) AS st2";
            if (el == "cc1")
                el = "public.hex_literal(cc1, 4) AS cc1";
            if (el == "cc2")
                el = "public.hex_literal(cc2, 4) AS cc2";
            if (el == "ss1")
                el = "public.hex_literal(ss1, 4) AS ss1";
            if (el == "ss2")
                el = "public.hex_literal(ss2, 4) AS ss2";
            if (el == "post")
                el = "public.hex_literal(post, 4) AS post";
            data.push_back(el + ", ");
        }

    }
    data.remove(data.size() - 2, data.size() - 1);
    model->setQuery("SELECT " + data + " FROM " + m_query_param[QP_TYPE_DEV] + "." + m_query_param[QP_TYPE_ARR]
                    + " "
                      "WHERE host_id='04:92:26:d0:ef:d6'::macaddr "
                      "AND experiment_id='" + m_kia_settings->m_kias_db->m_experiment_id + "' AND serial_num=" + m_query_param[QP_NUM_BOKZ]
                    + " AND datetime >= '" + QDate::currentDate().toString("yyyy-MM-dd") + " "
                    + begin + "' AND datetime <='" + QDate::currentDate().toString("yyyy-MM-dd") + " " + end + "';", m_db);
    if (model->lastError().isValid())
        std::cout <<  model->lastError().text().toStdString() << std::endl;
    m_kias_data_from_db->m_model.push(model);
}

QStringList Kia_db::get_tables(QString type_dev)
{
    QStringList tables;
    if (!m_query->exec("SELECT table_name, table_schema FROM information_schema.tables "
                       "where table_schema = '" + type_dev + "' and table_name not LIKE '%\\_%%';"))
    {
        qDebug() <<"Unable to execute query";
    }
    QSqlRecord rec = m_query->record();
    while(m_query->next())
    {
        tables.push_back(m_query->value(rec.indexOf("table_name")).toString());
    }
    return tables;
}

QStringList Kia_db::get_columns(QString type_dev, QString name_table)
{
    QStringList tables;
    if (!m_query->exec("SELECT column_name FROM information_schema.columns WHERE table_schema = '" + type_dev + "' AND table_name   = '" + name_table + "';"))
    {
        qDebug() <<"Unable to execute query";
    }
    QSqlRecord rec = m_query->record();
    while(m_query->next())
    {
        tables.push_back(m_query->value(rec.indexOf("column_name")).toString());
    }
    return tables;
}

QString Kia_db::get_columns_description(QString type_dev, QString name_table, QString id)
{
    QString description;
    if (!m_query->exec("SELECT description FROM meta_device.field WHERE devtype_id = '" + type_dev + "' AND struct_id   = '" + name_table + "' AND id = '" + id + "';"))
    {
        qDebug() <<"Unable to execute query";
    }
    QSqlRecord rec = m_query->record();
    while(m_query->next())
    {
        description = m_query->value(rec.indexOf("description")).toString();
    }
    return description;
}

QStringList Kia_db::get_query_param()
{
    return m_query_param;
}

void Kia_db::set_query(QStringList data_to_query, QStringList data)
{
    m_query_param = data_to_query;
    m_data = data;
}

QSqlDatabase Kia_db::get_data_base()
{
    return m_db;
}


