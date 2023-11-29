#include "kia_graph.h"
#include <QDebug>
Kia_graph::Kia_graph(std::shared_ptr<Kia_db> kia_db,
                     std::shared_ptr<Kia_settings> kia_settings,
                     std::shared_ptr<Kias_data_from_db> kias_graph_data,
                     QWidget *parent) :
    QCustomPlot(parent),
    m_kia_db(kia_db),
    m_kia_settings(kia_settings),
    m_kias_graph_data(kias_graph_data)
{
    m_clipboard = QApplication::clipboard();
}


Kia_graph::~Kia_graph()
{

}

void Kia_graph::init_timestamp_plot()
{
    connect(this, SIGNAL(get_data_from_db(QString, QString)), m_kia_db.get(), SLOT(get_data_from_db_for_graph_slot(QString, QString)));
    connect(this, SIGNAL(send_data_on_plot()), this, SLOT(set_data_on_plot_slot()));
    connect(this, SIGNAL(change_range()), this, SLOT(change_range_slot()));
    set_style();
    setAttribute(Qt::WA_OpaquePaintEvent);
    setNoAntialiasingOnDrag(true);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    addGraph();
    graph()->setScatterStyle(QCPScatterStyle::ssDisc);
    graph()->setLineStyle(QCPGraph::lsNone);
    create_context_menu();
    //    connect(this, &QCustomPlot::mouseMove, [this](auto e)
    //    {
    //        int mouseX = xAxis->pixelToCoord(e->pos().x());
    //        int mouseY = yAxis->pixelToCoord(e->pos().y());
    //        int index = graph()->findBegin(mouseX);
    //        int x = graph()->dataMainKey(index);
    //        int y = graph()->dataMainValue(index);
    //        QCPDataSelection selection = graph()->selection();
    //        if (((x >= (mouseX - 1)) && (x <= (mouseX + 1))) && ((y >= (mouseY - 1)) && (y <= (mouseY + 1))))
    //        {
    //            QString text = QString("%1 = %2").arg(m_query_param[QP_X]).arg(m_kias_graph_data->m_x_value[index].toDouble());
    //            QToolTip::showText(e->globalPos(), text);
    //        }

    //    });
    if (m_kias_graph_data->m_is_main_graph)
    {
        yAxis->setOffset(120);
        yAxis->setVisible(false);
        yAxis->grid()->setVisible(false);
        yAxis->setTicks(false);
        yAxis->setSubTicks(false);
        yAxis->setTickLabels(false);
        setInteraction(QCP::iRangeZoom, false);
        axisRect()->setAutoMargins(QCP::msBottom);
        axisRect()->setMargins(QMargins(0,0,0,0));
    }
}

void Kia_graph::init_default_plot()
{
    connect(this, SIGNAL(get_data_from_db(QString, QString)), m_kia_db.get(), SLOT(get_data_from_db_for_graph_slot(QString, QString)));
    connect(this, SIGNAL(send_data_on_plot()), this, SLOT(set_data_on_plot_slot()));
    connect(this, SIGNAL(change_range_default()), this, SLOT(change_range_default_slot()));
    set_style();
    setAttribute(Qt::WA_OpaquePaintEvent);
    setNoAntialiasingOnDrag(true);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    addGraph();
    graph()->setScatterStyle(QCPScatterStyle::ssDisc);
    graph()->setLineStyle(QCPGraph::lsNone);
    create_context_menu();
}

void Kia_graph::clear_clipboard_buffer()
{
    m_clipboard->clear();
}

void Kia_graph::set_style()
{
    QList<QCPAxis*> axises  = {xAxis, yAxis};
    for (auto a : axises)
    {
        a->setBasePen(QPen(Qt::black, 1));
        a->setTickPen(QPen(Qt::black, 1));
        a->setSubTickPen(QPen(Qt::black, 1));
        a->setTickLabelColor(Qt::black);
        a->grid()->setPen(QPen(Qt::gray, 1, Qt::DotLine));
        //a->grid()->setSubGridPen(QPen(Qt::gray, 0, Qt::DotLine));
        a->grid()->setSubGridVisible(false);
        a->grid()->setZeroLinePen(Qt::NoPen);
        a->setLabelColor(Qt::black);
        QFont font("JetBrains Mono ExtraLight", 10);
        a->setLabelFont(font);
        a->setTickLabelFont(font);
    }
    setBackground(QColor{255,255,255});
    replot();
}

void Kia_graph::keyPressEvent(QKeyEvent *e)
{
    if(e->type() == QKeyEvent::KeyPress)
        if(e->matches(QKeySequence::Copy))
        {
            QImage img = toPixmap().toImage();
            m_clipboard->setImage(img, QClipboard::Clipboard);
        }
}

void Kia_graph::get_data_from_db_slot()
{
    start_get_data = std::async([this]()
    {
        if (m_kia_settings->m_kias_db->m_key <= last_point_key)
            last_point_key = m_kia_settings->m_kias_db->m_key;
        if (m_kia_settings->m_kias_db->m_key - last_point_key >= 1)
        {
            if (!m_kias_graph_data->m_is_default_graph)
            {
                m_begin = QTime(0, 0, 0).addMSecs((xAxis->range().lower) * 1000);
                m_end = QTime(0, 0, 0).addMSecs((xAxis->range().upper) * 1000);
            }
            if (!m_kias_graph_data->m_is_main_graph)
            {
                if (!m_kias_graph_data->m_is_default_graph)
                {
                    emit get_data_from_db(m_begin.toString("hh:mm:ss.zzz"), m_end.toString("hh:mm:ss.zzz"));
                }
                else
                    emit get_data_from_db(m_kia_settings->m_kias_db->m_begin.toString("hh:mm:ss.zzz"), m_kia_settings->m_kias_db->m_end.toString("hh:mm:ss.zzz"));
                emit send_data_on_plot();
            }
            else
            {
                m_kia_settings->m_kias_db->m_begin = m_begin;
                m_kia_settings->m_kias_db->m_end = m_end;
            }
            last_point_key = m_kia_settings->m_kias_db->m_key;
        }
        if (!m_kias_graph_data->m_is_default_graph)
        {
            emit change_range();
        }
        else
            emit change_range_default();
    });

}

void Kia_graph::set_data_on_plot_slot()
{
    if (!m_kias_graph_data->m_is_default_graph)
    {
        for (uint16_t ind = 0; ind < m_kias_graph_data->m_date_time_val.size(); ind++)
        {
            double y_value = 0;
            if (m_is_degr_sec_or_nothing == DEGREEZ)
                y_value = get_degreze(m_kias_graph_data->m_y_value[ind]);
            else if(m_is_degr_sec_or_nothing == SECOND)
                y_value = get_seconds(m_kias_graph_data->m_y_value[ind]);
            else
                y_value = m_kias_graph_data->m_y_value[ind].toDouble();
            QTime timeStart = m_kias_graph_data->m_date_time_val[ind].toTime();
            double key = QTime(0, 0, 0).secsTo(timeStart);
            m_xData.push_back(key);
            m_yData.push_back(y_value);
        }
        graph()->setData(m_xData, m_yData);
    }
    else
    {
        for (uint16_t ind = 0; ind < m_kias_graph_data->m_x_value.size(); ind++)
        {
            double x_value = 0;
            double y_value = 0;
            if (m_is_degr_sec_or_nothing == DEGREEZ)
            {
                x_value = get_degreze(m_kias_graph_data->m_x_value[ind]);
                y_value = get_degreze(m_kias_graph_data->m_y_value[ind]);
            }
            else if(m_is_degr_sec_or_nothing == SECOND)
            {
                x_value = get_seconds(m_kias_graph_data->m_x_value[ind]);
                y_value = get_seconds(m_kias_graph_data->m_y_value[ind]);
            }
            else
            {
                x_value = m_kias_graph_data->m_x_value[ind].toDouble();
                y_value = m_kias_graph_data->m_y_value[ind].toDouble();
            }
            m_xData.push_back(x_value);
            m_yData.push_back(y_value);
        }
        graph()->setData(m_xData, m_yData);
    }
    m_xData.clear();
    m_yData.clear();
}

void Kia_graph::change_range_slot()
{
    if (m_kia_settings->m_kias_view_data->m_is_change_range)
    {
        auto interface = plottable();

        constexpr double k = 0.2;

        QList<double> ys;
        auto size = graph()->dataCount();
        if (size > 0)
        {
            auto last = interface->interface1D()->dataMainValue(size-1);
            ys.append(last);
        }
        if (!ys.isEmpty())
        {
            auto currentRange = yAxis->range();
            double lower = currentRange.lower + 0.10*currentRange.size();
            double upper = currentRange.upper - 0.10*currentRange.size();
            auto yminmax = std::minmax_element(ys.begin(), ys.end());
            auto ymin = *yminmax.first; auto ymax = *yminmax.first;
            double lowerD = k * (lower - ymin);
            double upperD = k * (upper - ymax);
            if ((lowerD > 0) && (upperD < 0) && (ymin != ymax)) //сжатие
            {
                yAxis->setRange(currentRange.lower - lowerD, currentRange.upper - upperD);
            }
            else if (lowerD > 0)
            {
                yAxis->setRange(currentRange.lower - lowerD, currentRange.upper - lowerD);
            }
            else if (upperD < 0)
            {
                yAxis->setRange(currentRange.lower - upperD, currentRange.upper - upperD);
            }
        }

        xAxis->setRange(m_kia_settings->m_kias_db->m_key, m_kia_settings->m_kias_view_data->m_x_size, Qt::AlignRight);
        replot(QCustomPlot::rpQueuedReplot);
        update();
    }

}

void Kia_graph::change_range_default_slot()
{
    auto interface = plottable();

    constexpr double k = 0.2;

    QList<double> ys;
    auto size = graph()->dataCount();
    if (size > 0)
    {
        auto last = interface->interface1D()->dataMainValue(size-1);
        ys.append(last);
    }
    if (!ys.isEmpty())
    {
        auto currentRange = yAxis->range();
        double lower = currentRange.lower + 0.10*currentRange.size();
        double upper = currentRange.upper - 0.10*currentRange.size();
        auto yminmax = std::minmax_element(ys.begin(), ys.end());
        auto ymin = *yminmax.first; auto ymax = *yminmax.first;
        double lowerD = k * (lower - ymin);
        double upperD = k * (upper - ymax);
        if ((lowerD > 0) && (upperD < 0) && (ymin != ymax)) //сжатие
        {
            yAxis->setRange(currentRange.lower - lowerD, currentRange.upper - upperD);
        }
        else if (lowerD > 0)
        {
            yAxis->setRange(currentRange.lower - lowerD, currentRange.upper - lowerD);
        }
        else if (upperD < 0)
        {
            yAxis->setRange(currentRange.lower - upperD, currentRange.upper - upperD);
        }
    }
    QList<double> xs;
    if (size > 0)
    {
        auto last = interface->interface1D()->dataMainKey(size-1);
        xs.append(last);
    }
    if (!xs.isEmpty())
    {
        auto currentRange = xAxis->range();
        double lower = currentRange.lower + 0.10*currentRange.size();
        double upper = currentRange.upper - 0.10*currentRange.size();
        auto xminmax = std::minmax_element(xs.begin(), xs.end());
        auto xmin = *xminmax.first; auto xmax = *xminmax.first;
        double lowerD = k * (lower - xmin);
        double upperD = k * (upper - xmax);
        if ((lowerD > 0) && (upperD < 0) && (xmin != xmax)) //сжатие
        {
            xAxis->setRange(currentRange.lower - lowerD, currentRange.upper - upperD);
        }
        else if (lowerD > 0)
        {
            xAxis->setRange(currentRange.lower - lowerD, currentRange.upper - lowerD);
        }
        else if (upperD < 0)
        {
            xAxis->setRange(currentRange.lower - upperD, currentRange.upper - upperD);
        }
    }
    replot(QCustomPlot::rpQueuedReplot);
    update();
}

void Kia_graph::create_context_menu()
{
    if (!m_kias_graph_data->m_is_main_graph)
    {
        m_context_menu = new QMenu(this);
        setContextMenuPolicy(Qt::CustomContextMenu);

        connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_context_menu(QPoint)));
        QAction* is_sec_or_degr = new QAction("Градусы", this);
        is_sec_or_degr->setCheckable(true);
        m_query_param = m_kia_db->get_query_param();
        if (m_query_param[QP_Y] == "alpha" || m_query_param[QP_Y] == "delta" || m_query_param[QP_Y] == "azimuth")
        {
            m_is_degr_sec_or_nothing = DEGREEZ;
            connect(is_sec_or_degr, &QAction::triggered, this, [this, is_sec_or_degr]()
            {
                if (is_sec_or_degr->isChecked())
                {
                    m_is_degr_sec_or_nothing = SECOND;
                    is_sec_or_degr->setText("Секунды");
                }
                else
                {
                    m_is_degr_sec_or_nothing = DEGREEZ;
                    is_sec_or_degr->setText("Градусы");
                }

            });

            m_context_menu->addAction(is_sec_or_degr);
        }
        QAction* clear_action = new QAction("Очистить", this);

        connect(clear_action, &QAction::triggered, this, [this]()
        {
            graph()->data()->clear();
            replot();

        });
        m_context_menu->addAction(clear_action);

        QAction* save_image_action = new QAction("Сохранить изображение", this);

        connect(save_image_action, &QAction::triggered, this, [this]()
        {
            saveBmp("/home/alexander/Project/kia_gui/graphs/graph_" + m_query_param[QP_X]
                    + "_" + m_query_param[QP_Y]
                    + "_" + m_query_param[QP_NUM_WIDGET] + ".bmp");

        });
        m_context_menu->addAction(save_image_action);


    }
}

void Kia_graph::show_context_menu(QPoint point)
{
    m_context_menu->popup(mapToGlobal(point));
}

double Kia_graph::get_degreze(QVariant &value)
{
    auto ret = value.toDouble() * 180 / PI;
    return ret;
}

double Kia_graph::get_seconds(QVariant &value)
{
    auto ret = value.toDouble() * 180 / PI;
    ret = ret * 3600;
    return ret;
}
