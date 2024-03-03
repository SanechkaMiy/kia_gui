#ifndef KIA_DB_H
#define KIA_DB_H
#include "Kia_main_struct.h"
#include <QSqlQueryModel>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QTime>
#include <QSqlQuery>
class Kia_db : public QObject
{
    Q_OBJECT
public:
    Kia_db(const QString &name_connection,
           std::shared_ptr<Kias_data_from_db> kias_data_from_db = nullptr);
    ~Kia_db();
    bool create_connection(const QString &name_connection);
    QStringList get_tables(QString type_dev);
    QStringList get_columns(QString type_dev, QString name_table);
    QString get_columns_description(QString type_dev, QString name_table, QString id);
    uint16_t is_array(QString type_dev, QString name_table, QString id);
    QString get_columns_units_of_measurement(QString type_dev, QString name_table, QString id);
    QStringList get_query_param();
    void set_query(QStringList data_to_query, QStringList data = QStringList());
    QSqlDatabase get_data_base();
private slots:
    void get_data_from_db_for_graph_slot(QString begin, QString end);
    void get_data_from_db_for_table_slot(QString begin, QString end);
private:
    std::shared_ptr<Kias_data_from_db> m_kias_data_from_db;
    QSqlQuery* m_query;
    QStringList m_query_param;
    QStringList m_data;
    QSqlDatabase m_db;
    QString m_name_connection;
};

#endif // KIA_DB_H
