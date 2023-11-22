#ifndef KIA_GRAPH_MANAGER_H
#define KIA_GRAPH_MANAGER_H
#include <QObject>
#include <QDialog>
#include "kia_db.h"
#include "kia_graph.h"
#include "Kia_main_struct.h"
#include "kia_constructor.h"
#include "kia_custom_dialog.h"
class Kia_graph_manager : public QObject
{
    Q_OBJECT
public:
    Kia_graph_manager(std::shared_ptr<Kia_settings> kia_settings,
                      std::shared_ptr<Kia_constructor> kia_constructor,
                      QWidget *parent);
    ~Kia_graph_manager();
    QVector<QDialog*> get_graph_widget();
    QDialog* get_main_graph_widget();
public slots:
    void show_graphs(int32_t num_plot);
signals:
    void create_action(QString, int32_t);
    void remove_action(int32_t);
    void set_default_pos();
private slots:
    void create_plot_slot(QStringList query_param);
    void remove_plot_slot(qint16 num_graph);
    void resize_window(qint16 num_graph, qint16 width, qint16 height);
private:

    QWidget* m_parent;
    void plots_interactions();
    void start_data_timer(Kia_graph *graph);
    void start_data_timer_for_default_plot(Kia_graph *graph);
    void init_graph_manager();
    void create_main_graph();
    QVector<QVBoxLayout*>m_l_for_plots;
    QVector<QDialog*> m_dialog;
    QVector<Kia_custom_dialog*> m_kia_custom_dialog;
    QDialog* m_main_dialog;
    std::vector<std::shared_ptr<Kias_data_from_db>> m_kias_data_from_db;
    QVector<Kia_graph*> m_kia_graph;
    Kia_graph* m_main_graph;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::vector<std::shared_ptr<Kia_db>> m_kia_db;
    std::shared_ptr<Kia_constructor> m_kia_constructor;
    std::shared_ptr<QTimer> m_timer;
    QStringList m_query_param;
    int32_t m_num_graph = -1;
};

#endif // KIA_GRAPH_MANAGER_H
