#ifndef KIA_TABLE_MANAGER_H
#define KIA_TABLE_MANAGER_H
#include <QObject>
#include <QTableView>
#include "kia_db.h"
#include <QObject>
#include <QVBoxLayout>
#include <QDialog>
#include "Kia_main_struct.h"
#include "kia_constructor.h"
#include <QSqlQueryModel>
#include "kia_custom_dialog.h"
#include "kia_table/kia_tables.h"
#include <QTimer>
class Kia_table_manager : public QObject
{
    Q_OBJECT
public:
    Kia_table_manager(std::shared_ptr<Kia_settings> kia_settings,
                      std::shared_ptr<Kia_constructor> kia_constructor,
                      QWidget *parent, QWidget *m_default_parent);
    QVector<QDialog*> get_table_widgets();
    Kia_custom_dialog* get_table_widget(uint16_t num_table);
    ~Kia_table_manager();
public slots:
    void show_tables(int32_t num_table);
private slots:
    void create_table_slot(QStringList query_param, QStringList data);
    void remove_table_slot(qint16 num_table);
signals:
    void create_action(QString, int32_t);
    void remove_action(int32_t);
private:
    int32_t m_num_table = -1;
    QWidget* m_parent;
    QWidget* m_default_parent;
    QVector<QVBoxLayout*> m_l_for_tables;
    QVector<Kia_custom_dialog*> m_kia_custom_dialog;
    QVector<QDialog*> m_dialog;
    QVector<Kia_tables*> m_kia_tables;
    std::vector<std::shared_ptr<Kias_data_from_db>> m_kias_data_from_db;
    std::shared_ptr<Kia_settings> m_kia_settings;
    void init_table_manager();
    std::shared_ptr<QTimer> m_timer;
    void start_data_timer(int32_t& num_graph);
    std::vector<std::shared_ptr<Kia_db>> m_kia_db;
    std::shared_ptr<Kia_constructor> m_kia_constructor;
};

#endif // KIA_TABLE_MANAGER_H
