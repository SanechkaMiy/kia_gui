#ifndef KIA_CONSTRUCTOR_H
#define KIA_CONSTRUCTOR_H
#include <QDialog>
#include "kia_db.h"
#include <future>
#include "Kia_main_struct.h"
#include <QCheckBox>
#include <QListWidgetItem>
namespace Ui {
class Kia_constructor;
}

class Kia_constructor : public QDialog
{
    Q_OBJECT

public:
    explicit Kia_constructor(std::shared_ptr<Kia_settings> kia_settings,
                             QWidget *parent = nullptr);
    ~Kia_constructor();
    void set_type_dev(uint16_t type_bokz, uint16_t type_bi);
    void add_graph();
    void add_table();
    void add_graph_to_list(QStringList query_param);
    void add_table_to_list(QStringList query_param);
    void set_active(const uint16_t &index_tab);
    void stop_thread();
    void remove_list();
signals:
    void add_graph(QStringList);
    void set_window_initial_settings(qint16, qint16, qint16);
    void remove_graph(qint16);
    void show_graph(int32_t);

    void add_table(QStringList, QStringList);
    void remove_table(qint16);
    void show_table(int32_t);

private slots:
    void on_pb_add_graph_clicked();

    void on_pb_remove_graph_clicked();

    void on_pb_add_table_clicked();

    void on_pb_remove_table_clicked();

    void on_pb_show_graph_clicked();

    void on_pb_graph_angles_clicked();

private:
    void start_thread();
    Ui::Kia_constructor *ui;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Kia_db> m_kia_db;
    QString m_type_dev;
    QString m_type_arr;
    QString m_x_val;
    QString m_y_val;
    QString m_x_desc;
    QString m_y_desc;
    QString m_x_um;
    QString m_y_um;
    QString m_type_widget;
    QStringList m_data_table;
    QListWidgetItem * m_cur_graph;
    std::vector<QCheckBox*> m_cb_for_data;
    std::future<void> m_thread_change_range;
    std::atomic_bool m_stop_change_range{false};

    QDialog* m_select_dev_for_plot;
    std::vector<uint16_t> m_selected_bokz;
};

#endif // KIA_CONSTRUCTOR_H
