#ifndef KIA_GRAPH_H
#define KIA_GRAPH_H

#include "Kia_main_struct.h"
#include <QVariant>
#include "kia_db.h"
#include <qcustomplot.h>
#include <future>
#include <QList>
#include <QMenu>
#include <QMouseEvent>
#include <QKeyEvent>
namespace Ui {
class Kia_graph;
}

class Kia_graph : public QCustomPlot
{
    Q_OBJECT
private:
    std::shared_ptr<Kia_db> m_kia_db;
    std::shared_ptr<Kia_settings> m_kia_settings;
public:
    explicit Kia_graph(std::shared_ptr<Kia_db> kia_db,
                       std::shared_ptr<Kia_settings> kia_settings,
                       std::shared_ptr<Kias_data_from_db> kias_graph_data,
                       QWidget *parent = nullptr);
    void init_timestamp_plot();
    void init_default_plot();
    void clear_clipboard_buffer();
    std::shared_ptr<Kias_data_from_db> m_kias_graph_data;
    ~Kia_graph();
signals:
    void get_data_from_db(QString, QString);
    void send_data_on_plot();
    void change_range();

private slots:
    void get_data_from_db_slot();
    void set_data_on_plot_slot();
    void change_range_slot();
    void change_range_default_slot();
    void create_context_menu();
    void show_context_menu(QPoint point);
private:
    QClipboard* m_clipboard;
    double get_degreze(QVariant& value);
    double get_seconds(QVariant& value);
    QMenu* m_context_menu;
    QStringList m_query_param;
    double m_size = 8;
    double last_point_key = 0;
    void start_data_timer();
    void set_style();
    QVector<double> m_xData, m_yData;
    uint16_t m_is_degr_sec_or_nothing = NOTHING;
    double m_start_time = 0;
    std::future<void> start_get_data;
    QTime m_begin;
    QTime m_end;
protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // KIA_GRAPH_H
