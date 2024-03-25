#ifndef KIA_TABLES_H
#define KIA_TABLES_H

#include "Kia_main_struct.h"
#include <QTableView>
#include <future>
#include "kia_db.h"
class Kia_tables: public QTableView
{
    Q_OBJECT
public:
    explicit Kia_tables(std::shared_ptr<Kia_db> kia_db,
                        std::shared_ptr<Kia_settings> kia_settings,
                        std::shared_ptr<Kias_data_from_db> kias_graph_data,
                        QWidget *parent = nullptr);
signals:
    void get_data_from_db(QString, QString);
    void send_data_on_table();
    void set_default_pos();
private slots:
    void get_data_from_db_slot();
    void set_data_on_table_slot();
private:
    QWidget* m_parent;
    std::shared_ptr<Kia_db> m_kia_db;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Kias_data_from_db> m_kias_graph_data;
    std::future<void> start_get_data;
    double last_point_key = 0;
protected:
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // KIA_TABLES_H
