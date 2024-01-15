#include "kia_graph_manager.h"

Kia_graph_manager::Kia_graph_manager(std::shared_ptr<Kia_settings> kia_settings,
                                     std::shared_ptr<Kia_constructor> kia_constructor,
                                     QWidget *parent, QWidget* m_default_parent) :
    m_parent(parent),
    m_default_parent(m_default_parent),
    m_kia_settings(kia_settings),
    m_kia_constructor(kia_constructor)
{
    init_graph_manager();
    connect(m_kia_constructor.get(), SIGNAL(add_graph(QStringList)), this, SLOT(create_plot_slot(QStringList)));
    connect(m_kia_constructor.get(), SIGNAL(remove_graph(qint16)), this, SLOT(remove_plot_slot(qint16)));
    connect(m_kia_constructor.get(), SIGNAL(show_graph(int32_t)), this, SLOT(show_graphs(int32_t)));
    connect(m_kia_constructor.get(), SIGNAL(set_window_initial_settings(qint16, qint16, qint16)), this, SLOT(resize_window(qint16, qint16, qint16)));
    create_main_graph();
}

void Kia_graph_manager::init_graph_manager()
{
    m_timer = std::make_shared<QTimer>();
    m_timer->start(0);
}

void Kia_graph_manager::create_main_graph()
{
    m_main_dialog = new QDialog(m_parent);
    m_main_dialog->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
    m_main_dialog->setMaximumHeight(60);
    m_main_dialog->setMinimumHeight(60);
    m_main_dialog->setWindowFlags(Qt::WindowShadeButtonHint);
    auto l_for_plot = new QHBoxLayout(m_main_dialog);
    auto kias_data_from_db = std::make_shared<Kias_data_from_db>();
    kias_data_from_db->m_graph_type = Kia_graph::MAIN_GRAPH;
    auto kia_db = std::make_shared<Kia_db>("con_main_graph", m_kia_settings, kias_data_from_db);
    m_main_graph = new Kia_graph(kia_db, m_kia_settings, kias_data_from_db, m_main_dialog);
    m_main_graph->init_timestamp_plot();
    l_for_plot->addWidget(m_main_graph);
    plots_interactions();
    start_data_timer(m_main_graph);
}


Kia_graph_manager::~Kia_graph_manager()
{
    for (auto plot : m_kia_graph)
    {
        if(plot->m_kias_graph_data->m_graph_type != Kia_graph::MAIN_GRAPH)
        {
            plot->clear_clipboard_buffer();
        }
    }
    std::cout << "desctr graph_manager" << std::endl;
}


//void Kia_graph_manager::create_plot_slot(QStringList query_param)
//{

//    m_num_graph++;
//    m_dialog.push_back(new QDialog(m_parent));
//    m_l_for_plots.push_back(new QVBoxLayout(m_dialog[m_num_graph]));
//    m_kias_data_from_db.push_back(std::make_shared<Kias_data_from_db>());
//    m_kia_db.push_back(std::make_shared<Kia_db>("con_graph_" + QString::number(m_num_graph), m_kia_settings, m_kias_data_from_db[m_num_graph]));
//    m_kia_db[m_num_graph]->set_query(query_param);
//    m_kia_graph.push_back(new Kia_graph(m_kia_db[m_num_graph], m_kia_settings, m_kias_data_from_db[m_num_graph], m_dialog[m_num_graph]));
//    if (query_param[QP_TYPE_WIDGET] == "datetime")
//    {
//        m_kias_data_from_db[m_num_graph]->m_is_default_graph = false;
//        m_kia_graph[m_num_graph]->init_timestamp_plot();
//        start_data_timer(m_kia_graph[m_num_graph]);
//    }
//    else
//    {
//        m_kias_data_from_db[m_num_graph]->m_is_default_graph = true;
//        m_kia_graph[m_num_graph]->init_default_plot();
//        start_data_timer_for_default_plot(m_kia_graph[m_num_graph]);
//    }
//    m_kia_graph[m_num_graph]->xAxis->setLabel(query_param[QP_X_DESC]);
//    m_kia_graph[m_num_graph]->yAxis->setLabel(query_param[QP_Y_DESC]);
//    m_l_for_plots[m_num_graph]->addWidget(m_kia_graph[m_num_graph]);
//    plots_interactions();
//    m_kia_constructor->add_graph_to_list(query_param);
//    m_dialog[m_num_graph]->setWindowTitle("График " + query_param[QP_Y_DESC]
//                                          + " от " + query_param[QP_X_DESC]
//                                          + " " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]

//            + " " + QString::number(query_param[QP_NUM_BOKZ].toInt() + 1));
//    emit create_action("График " + query_param[QP_Y_DESC]
//                       + " от " + query_param[QP_X_DESC]
//                       + " " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
//            + " " + QString::number(query_param[QP_NUM_BOKZ].toInt() + 1), m_num_graph);

//}


void Kia_graph_manager::create_plot_slot(QStringList query_param)
{
    m_num_graph++;
    auto parent = m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[query_param[QP_NUM_MAIN_TAB_WIDGET].toInt()];
    if (m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[query_param[QP_NUM_MAIN_TAB_WIDGET].toInt()])
    {
        parent = m_default_parent;
    }
    m_kia_custom_dialog.push_back(new Kia_custom_dialog(parent));
    connect(this, SIGNAL(set_default_pos()), m_kia_custom_dialog[m_num_graph], SLOT(set_default_pos_slot()));
    m_dialog.push_back(new QDialog());
    m_l_for_plots.push_back(new QVBoxLayout(m_dialog[m_num_graph]));
    m_kias_data_from_db.push_back(std::make_shared<Kias_data_from_db>());
    m_kia_db.push_back(std::make_shared<Kia_db>("con_graph_" + QString::number(m_num_graph), m_kia_settings, m_kias_data_from_db[m_num_graph]));
    m_kia_db[m_num_graph]->set_query(query_param);
    m_kia_graph.push_back(new Kia_graph(m_kia_db[m_num_graph], m_kia_settings, m_kias_data_from_db[m_num_graph]));
    m_kia_graph[m_num_graph]->xAxis->setLabel(query_param[QP_X_DESC]);
    m_kia_graph[m_num_graph]->yAxis->setLabel(query_param[QP_Y_DESC]);
    if (query_param[QP_TYPE_WIDGET] == "datetime")
    {
        m_kias_data_from_db[m_num_graph]->m_graph_type = Kia_graph::TIMESTAMP_GRAPH;
        m_kia_graph[m_num_graph]->init_timestamp_plot();
        start_data_timer(m_kia_graph[m_num_graph]);
    }
    else
    {
        m_kias_data_from_db[m_num_graph]->m_graph_type = Kia_graph::DEFAULT_GRAPH;
        m_kia_graph[m_num_graph]->init_default_plot();
        start_data_timer_for_default_plot(m_kia_graph[m_num_graph]);
    }
    m_l_for_plots[m_num_graph]->addWidget(m_kia_graph[m_num_graph]);
    m_kia_custom_dialog[m_num_graph]->set_wiget_to_layout(m_dialog[m_num_graph]);
    plots_interactions();
    m_kia_constructor->add_graph_to_list(query_param);


    QString title = "График " + query_param[QP_Y_DESC]
            + " от " + query_param[QP_X_DESC]
            + " " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
            + " " + QString::number(query_param[QP_NUM_BOKZ].toInt() + 1);
    if (!query_param[QP_NUM_BOKZ_FOR_ANGLES].isEmpty())
    {
        title = title + " и " + m_kia_settings->m_kia_bokz_settings->m_bokz_type[m_kia_settings->m_type_bokz]
                + " " + QString::number(query_param[QP_NUM_BOKZ_FOR_ANGLES].toInt() + 1);
    }
    m_dialog[m_num_graph]->setWindowTitle(title);
    m_kia_custom_dialog[m_num_graph]->set_window_title(title);

    emit create_action(title, m_num_graph);
}

void Kia_graph_manager::remove_plot_slot(qint16 num_graph)
{
    delete m_kia_graph[num_graph];
    m_kia_db[num_graph].reset();
    m_kias_data_from_db[num_graph].reset();
    delete m_l_for_plots[num_graph];
    delete m_dialog[num_graph];
    disconnect(this, SIGNAL(set_default_pos()), m_kia_custom_dialog[num_graph], SLOT(set_default_pos_slot()));
    m_kia_settings->m_kia_gui_settings->m_current_num_parent.remove(m_kia_custom_dialog[num_graph]);
    delete m_kia_custom_dialog[num_graph];
    m_kia_graph.erase(m_kia_graph.begin() + num_graph);
    m_kia_db.erase(m_kia_db.begin() + num_graph);
    m_kias_data_from_db.erase(m_kias_data_from_db.begin() + num_graph);
    m_l_for_plots.erase(m_l_for_plots.begin() + num_graph);
    m_dialog.erase(m_dialog.begin() + num_graph);
    m_kia_custom_dialog.erase(m_kia_custom_dialog.begin() + num_graph);
    m_num_graph -= 1;
    emit remove_action(num_graph);
}

void Kia_graph_manager::resize_window(qint16 num_graph, qint16 width, qint16 height)
{
    m_kia_custom_dialog[num_graph]->resize(width, height);
}

void Kia_graph_manager::show_graphs(int32_t num_plot)
{
    m_kia_settings->m_kias_view_data->m_data_graph[num_plot][QP_NUM_MAIN_TAB_WIDGET] = QString::number(m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget);
    m_kia_custom_dialog[num_plot]->setParent(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget]);
    m_kia_custom_dialog[num_plot]->show();
    m_kia_settings->m_kia_gui_settings->m_current_num_parent[m_kia_custom_dialog[num_plot]] = m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget;
    m_kia_settings->m_kia_gui_settings->m_widget_is_hide[m_kia_custom_dialog[num_plot]] = m_kia_custom_dialog[num_plot]->isVisible();
}

QVector<QDialog*> Kia_graph_manager::get_graph_widgets()
{
    QVector<QDialog*> list_widget;
    for (auto el : m_kia_custom_dialog)
        list_widget.push_back(el);
    return list_widget;
}

QDialog *Kia_graph_manager::get_main_graph_widget()
{
    return m_main_dialog;
}

Kia_custom_dialog *Kia_graph_manager::get_graph_widget(uint16_t num_graph)
{
    return m_kia_custom_dialog[num_graph];
}

void Kia_graph_manager::plots_interactions()
{
    for (auto plot : m_kia_graph)
    {
        if (plot->m_kias_graph_data->m_graph_type != Kia_graph::MAIN_GRAPH)
        {
            plot->connect(plot, &QCustomPlot::mouseMove, [=](auto e)
            {


                Q_UNUSED(e)
                plot->setCursor(Qt::ArrowCursor);
                emit set_default_pos();
            });
        }
        if (plot->m_kias_graph_data->m_graph_type != Kia_graph::DEFAULT_GRAPH)
        {
            plot->connect(plot, &QCustomPlot::mouseWheel, [=](QWheelEvent* e)
            {
                m_kia_settings->m_kias_view_data->m_is_change_range = false;
                auto orient = (e->modifiers() != Qt::ControlModifier) ? Qt::Horizontal : Qt::Vertical;
                plot->axisRect()->setRangeZoom(orient);
                if (!(e->modifiers() == Qt::ControlModifier))
                {
                    if((e->angleDelta().y()) > 0)
                    {
                        if (m_kia_settings->m_kias_view_data->m_x_size > 1)
                            m_kia_settings->m_kias_view_data->m_x_size = m_kia_settings->m_kias_view_data->m_x_size - 0.5;

                    }
                    else
                    {
                        m_kia_settings->m_kias_view_data->m_x_size = m_kia_settings->m_kias_view_data->m_x_size + 0.5;
                    }
                }

                //plot->wheelEvent(e);
                e->accept();
                m_kia_settings->m_kias_view_data->m_is_change_range = true;
            });
            plot->connect(plot, &QCustomPlot::mousePress, [=](auto e)
            {
                if (e->buttons() == Qt::LeftButton && e->modifiers() == Qt::ControlModifier)
                {
                    plot->setInteraction(QCP::iRangeZoom);
                    plot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
                }
                else if (e->buttons() == Qt::LeftButton && e->modifiers() == Qt::NoModifier)
                {
                    plot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
                    m_kia_settings->m_kias_view_data->m_is_change_range = false;
                }
                QSharedPointer<QMetaObject::Connection> x(new QMetaObject::Connection);
                *x = plot->connect(plot, &QCustomPlot::beforeReplot, [=]()
                {
                    plot->disconnect(*x);
                });
            });

            plot->connect(plot, &QCustomPlot::mouseRelease, [=](auto e)
            {
                Q_UNUSED(e)
                m_kia_settings->m_kias_db->m_key = plot->xAxis->range().upper;
                m_kia_settings->m_kias_view_data->m_is_change_range = true;

            });

            connect(plot->xAxis, qOverload<const QCPRange&>(&QCPAxis::rangeChanged),
                    this, [this](const QCPRange& range)
            {
                for (auto plot : m_kia_graph)
                {
                    if (plot->m_kias_graph_data->m_graph_type != Kia_graph::DEFAULT_GRAPH)
                    {
                        plot->xAxis->setRange(range);
                        plot->replot(QCustomPlot::rpQueuedReplot);
                        plot->update();
                    }
                }
                m_main_graph->xAxis->setRange(range);
                m_main_graph->replot(QCustomPlot::rpQueuedReplot);
                m_main_graph->update();
            });
        }
        else
        {
            plot->connect(plot, &QCustomPlot::mouseWheel, [=](QWheelEvent* e)
            {
                auto orient = (e->modifiers() != Qt::ControlModifier) ? Qt::Horizontal : Qt::Vertical;
                plot->axisRect()->setRangeZoom(orient);
                //                if (!(e->modifiers() == Qt::ControlModifier))
                //                {
                //                    if((e->angleDelta().y()) > 0)
                //                    {
                //                        if (m_kia_settings->m_kias_view_data->m_x_size > 1)
                //                            m_kia_settings->m_kias_view_data->m_x_size = m_kia_settings->m_kias_view_data->m_x_size - 0.5;

                //                    }
                //                    else
                //                    {
                //                        m_kia_settings->m_kias_view_data->m_x_size = m_kia_settings->m_kias_view_data->m_x_size + 0.5;
                //                    }
                //                }

                //plot->wheelEvent(e);
                e->accept();
            });
        }
    }

    m_main_graph->connect(m_main_graph, &QCustomPlot::mouseWheel, [=](QWheelEvent* e)
    {
        m_kia_settings->m_kias_view_data->m_is_change_range = false;
        auto orient = (e->modifiers() != Qt::ControlModifier) ? Qt::Horizontal : Qt::Vertical;
        m_main_graph->axisRect()->setRangeZoom(orient);
        if (!(e->modifiers() == Qt::ControlModifier))
        {
            if((e->angleDelta().y()) > 0)
            {
                if (m_kia_settings->m_kias_view_data->m_x_size > 1)
                    m_kia_settings->m_kias_view_data->m_x_size = m_kia_settings->m_kias_view_data->m_x_size - 0.5;

            }
            else
            {
                m_kia_settings->m_kias_view_data->m_x_size = m_kia_settings->m_kias_view_data->m_x_size + 0.5;
            }
        }

        //plot->wheelEvent(e);
        e->accept();
        m_kia_settings->m_kias_view_data->m_is_change_range = true;
    });

    m_main_graph->connect(m_main_graph, &QCustomPlot::mousePress, [=](auto e)
    {
        if (e->buttons() == Qt::LeftButton && e->modifiers() == Qt::NoModifier)
        {
            m_main_graph->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
            m_kia_settings->m_kias_view_data->m_is_change_range = false;
        }
        QSharedPointer<QMetaObject::Connection> x(new QMetaObject::Connection);
        *x = m_main_graph->connect(m_main_graph, &QCustomPlot::beforeReplot, [=]()
        {
            m_main_graph->disconnect(*x);
        });
    });
    m_main_graph->connect(m_main_graph, &QCustomPlot::mouseRelease, [=](auto e)
    {
        m_kia_settings->m_kias_db->m_key = m_main_graph->xAxis->range().upper;
        m_kia_settings->m_kias_view_data->m_is_change_range = true;

    });

    connect(m_main_graph->xAxis, qOverload<const QCPRange&>(&QCPAxis::rangeChanged),
            this, [this](const QCPRange& range)
    {
        for (auto plot : m_kia_graph)

        {
            if (plot->m_kias_graph_data->m_graph_type != Kia_graph::DEFAULT_GRAPH)
            {
                plot->xAxis->setRange(range);
                plot->replot(QCustomPlot::rpQueuedReplot);
                plot->update();
            }
        }
    });


}

void Kia_graph_manager::start_data_timer(Kia_graph* graph)
{
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s.%z");
    graph->xAxis->setTicker(timeTicker);
    graph->axisRect()->setupFullAxesBox();
    //graph->yAxis->setRange(-1.2, 1.2);
    connect(graph->xAxis, SIGNAL(rangeChanged(QCPRange)), graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(graph->yAxis, SIGNAL(rangeChanged(QCPRange)), graph->yAxis2, SLOT(setRange(QCPRange)));
    // Interval 0 means to refresh as fast as possible
    connect(m_timer.get(), SIGNAL(timeout()), graph, SLOT(get_data_from_db_slot()));
}

void Kia_graph_manager::start_data_timer_for_default_plot(Kia_graph *graph)
{
    connect(m_timer.get(), SIGNAL(timeout()), graph, SLOT(get_data_from_db_slot()));
}

