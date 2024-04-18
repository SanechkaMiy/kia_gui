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
#include <functional>
#include <algorithm>
#include <thread>

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
    enum TYPE_GRAPH
    {
        MAIN_GRAPH = -1,
        TIMESTAMP_GRAPH = 0,
        DEFAULT_GRAPH = 1
    };
    enum TYPE_DATA_IF_CHANGE
    {
        NOTHING = -1,
        ANGLES = 0,
        SPEED = 1
    };

    enum TYPE_DATA_FOR_GRAPH
    {
        DEFAULT = 0,
        DEGREEZ = 1,
        SECOND = 2,
        DEGREEZ_IN_SEC = 3,
        RAD_IN_SEC = 4
    };
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
    void change_range_default();

private slots:
    void get_data_from_db_slot();
    void set_data_on_plot_slot();
    void change_range_slot();
    void change_range_default_slot();
    void create_context_menu();
    void show_context_menu(QPoint point);
private:
    QClipboard* m_clipboard;
    void check_data();
    double get_degreze(QVariant value);
    double get_seconds(QVariant value);
    double get_radians(QVariant value);
    void auto_scale();
    QAction* m_action_to_change_dimensions;
    QMenu* m_context_menu;
    QStringList m_query_param;
    double m_size = 8;
    double last_point_key = 0;
    void start_data_timer();
    void set_style();
    QVector<double> m_xData, m_yData;
    QVector<double> m_buffer_for_auto_scale;
    uint16_t m_is_value_or_nothing = DEFAULT;
    double m_start_time = 0;
    std::future<void> start_get_data;
    std::future<void> m_fut_do_auto_scale;
    QTime m_begin;
    QTime m_end;
    std::vector<std::function<void()>> m_func_for_graph_type;
    std::vector<std::function<void()>> m_func_for_data_type;
    QStringList m_do_convert_for_angle = {"alpha", "delta", "azimuth"};
    QStringList m_do_convert_for_speed = {"wox", "woy", "woz"};
    QStringList m_do_conver_if_tmprt = {"td_1"};
    int16_t m_data_type = NOTHING;
    bool m_is_show_mean = false;

    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
    {
        size_t pos = txt.find( ch );
        size_t initialPos = 0;
        strs.clear();

        // Decompose statement
        while( pos != std::string::npos ) {
            strs.push_back( txt.substr( initialPos, pos - initialPos ) );
            initialPos = pos + 1;

            pos = txt.find( ch, initialPos );
        }

        // Add the last one
        strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

        return strs.size();
    }

    std::atomic_bool m_do_auto_scale {false};
protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // KIA_GRAPH_H
