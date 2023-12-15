#include "kia_constructor.h"
#include "ui_kia_constructor.h"

Kia_constructor::Kia_constructor(std::shared_ptr<Kia_settings> kia_settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kia_constructor),
    m_kia_settings(kia_settings),
    m_kia_db(new Kia_db("constructor", m_kia_settings))
{
    ui->setupUi(this);
    start_thread();
}

Kia_constructor::~Kia_constructor()
{
    stop_thread();
    delete ui;
}

void Kia_constructor::set_active(const uint16_t& index_tab)
{
    ui->tabWidget->setCurrentIndex(index_tab);
}

void Kia_constructor::stop_thread()
{
    if (m_stop_change_range)
    {
        m_stop_change_range = false;
        m_thread_change_range.get();
    }
}


void Kia_constructor::set_type_dev(uint16_t type_bokz, uint16_t type_bi)
{

    ui->pb_show_graph->hide();
    ui->pb_show_table->hide();
    ui->lw_type_dev->clear();
    ui->lw_type_dev->addItem(m_kia_settings->m_kias_db->m_bokz_type[type_bokz]);
    ui->lw_type_dev->addItem(m_kia_settings->m_kias_db->m_bi_type[type_bi]);
    connect(ui->lw_type_dev, &QListWidget::itemClicked, this, [this](QListWidgetItem *type_dev)
    {
        ui->lw_type_arr->clear();
        QStringList name_tables;
        name_tables = m_kia_db->get_tables(type_dev->text());
        m_type_dev = type_dev->text();
        ui->lw_type_arr->addItems(name_tables);
    });

    connect(ui->lw_type_arr, &QListWidget::itemClicked, this, [this](QListWidgetItem *type_arr)
    {
        ui->lw_x->clear();
        ui->lw_y->clear();
        QStringList col;
        col = m_kia_db->get_columns(m_type_dev, type_arr->text());
        m_type_arr = type_arr->text();
        ui->lw_x->addItems(col);
        ui->lw_y->addItems(col);

    });

    connect(ui->lw_x, &QListWidget::itemClicked, this, [this](QListWidgetItem *x_val)
    {
        m_x_val = x_val->text();
        m_x_desc = m_kia_db->get_columns_description(m_type_dev, m_type_arr, m_x_val);

    });

    connect(ui->lw_y, &QListWidget::itemClicked, this, [this](QListWidgetItem *y_val)
    {
        m_y_val = y_val->text();
        m_y_desc = m_kia_db->get_columns_description(m_type_dev, m_type_arr, m_y_val);
    });


    connect(ui->lw_list_graph, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item)
    {
        Q_UNUSED(item)
        emit show_graph(ui->lw_list_graph->currentRow());
    });


    //table----
    ui->lw_type_dev_table->clear();
    ui->lw_type_dev_table->addItem(m_kia_settings->m_kias_db->m_bokz_type[type_bokz]);
    ui->lw_type_dev_table->addItem(m_kia_settings->m_kias_db->m_bi_type[type_bi]);
    connect(ui->lw_type_dev_table, &QListWidget::itemClicked, this, [this](QListWidgetItem *type_dev)
    {
        ui->lw_type_arr_table->clear();
        QStringList name_tables;
        name_tables = m_kia_db->get_tables(type_dev->text());
        m_type_dev = type_dev->text();
        ui->lw_type_arr_table->addItems(name_tables);
    });

    connect(ui->lw_type_arr_table, &QListWidget::itemClicked, this, [this](QListWidgetItem *type_arr)
    {
        for (auto el : m_cb_for_data)
            delete el;
        m_cb_for_data.clear();
        ui->lw_data_table->clear();
        QStringList col;
        col = m_kia_db->get_columns(m_type_dev, type_arr->text());
        m_type_arr = type_arr->text();
        m_data_table.clear();
        for (uint16_t coll = 0; coll < col.size(); ++coll)
        {
            m_data_table.push_back("");
            m_cb_for_data.push_back(new QCheckBox(col[coll], this));
            QListWidgetItem* item = new QListWidgetItem(ui->lw_data_table);
            ui->lw_data_table->setItemWidget(item, m_cb_for_data[coll]);
            connect(m_cb_for_data[coll], &QCheckBox::toggled,  ([this, coll](bool is_toggled)
            {
                if (is_toggled)
                    m_data_table[coll].push_back(m_cb_for_data[coll]->text());
                else
                    m_data_table[coll].clear();
            }));
        }

    });


}
void Kia_constructor::add_graph()
{
    for (int num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
        {
            QStringList query_param;
            query_param.push_back(m_x_val);
            query_param.push_back(m_y_val);
            query_param.push_back(m_type_dev);
            query_param.push_back(m_type_arr);
            query_param.push_back(m_x_desc);
            query_param.push_back(m_y_desc);
            query_param.push_back(QString::number(num_bokz));
            query_param.push_back(QString::number(m_kia_settings->m_kias_view_data->m_graph_count));
            query_param.push_back(m_type_widget);
            query_param.push_back(QString::number(m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget));
            m_kia_settings->m_kias_view_data->m_graph_count++;
            m_kia_settings->m_kias_view_data->m_data_graph.push_back(query_param);
            emit add_graph(query_param);
            emit set_window_initial_settings(query_param[QP_NUM_WIDGET].toInt(), 800, 500);
            emit show_graph(query_param[QP_NUM_WIDGET].toInt());
        }
    }
}

void Kia_constructor::add_table()
{
    QString type_dev = "bokz";
    bool is_bi = false;
    for (int num_bokz = 0; num_bokz < m_kia_settings->m_kia_bokz_settings->m_count_bokz; ++num_bokz)
    {
        if (m_kia_settings->m_kia_data_to_server->m_is_used_bokz[num_bokz] == CS_IS_ON)
        {
            QStringList query_param;
            query_param.push_back("");
            query_param.push_back("");
            query_param.push_back(m_type_dev);
            query_param.push_back(m_type_arr);
            query_param.push_back("");
            query_param.push_back("");
            auto name_dev = m_type_dev;
            name_dev.resize(type_dev.size());
            if (type_dev != name_dev)
            {
                is_bi = true;
            }
            if (is_bi)
                query_param.push_back(QString::number(m_kia_settings->m_kia_data_to_server->m_num_used_bi[num_bokz]));
            else
                query_param.push_back(QString::number(num_bokz));
            query_param.push_back(QString::number(m_kia_settings->m_kias_view_data->m_table_count));
            query_param.push_back(m_type_widget);
            query_param.push_back(QString::number(m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget));
            QStringList data;
            data.push_back(QString::number(m_kia_settings->m_kias_view_data->m_table_count));
            for (auto el : m_data_table)
                data.push_back(el);
            m_kia_settings->m_kias_view_data->m_table_count++;
            m_kia_settings->m_kias_view_data->m_data_table.push_back(query_param);
            m_kia_settings->m_kias_view_data->m_data_table_cols.push_back(data);
            emit add_table(query_param, m_data_table);
            emit show_table(query_param[QP_NUM_WIDGET].toInt());
        }
    }
}

void Kia_constructor::remove_graph_slot(uint16_t num_graph)
{
    if (ui->lw_list_graph->count() != 0)
    {
        if (num_graph + 1 < ui->lw_list_graph->count())
        {
            for (uint16_t ind = num_graph; ind < m_kia_settings->m_kias_view_data->m_data_graph.size(); ++ind)
                m_kia_settings->m_kias_view_data->m_data_graph[ind][QP_NUM_WIDGET] = QString::number(m_kia_settings->m_kias_view_data->m_data_graph[ind][QP_NUM_WIDGET].toUInt() - 1);
        }
        m_kia_settings->m_kias_view_data->m_data_graph.erase(m_kia_settings->m_kias_view_data->m_data_graph.begin() + num_graph);
        m_kia_settings->m_kias_view_data->m_graph_count -= 1;
        emit remove_graph(num_graph);
        delete ui->lw_list_graph->item(num_graph);
    }
}

void Kia_constructor::remove_table_slot(uint16_t num_table)
{
    if (ui->lw_list_table->count() != 0)
    {
        if (num_table + 1 < ui->lw_list_table->count())
        {
            for (uint16_t ind = num_table; ind < m_kia_settings->m_kias_view_data->m_data_table.size(); ++ind)
                m_kia_settings->m_kias_view_data->m_data_table[ind][QP_NUM_WIDGET] = QString::number(m_kia_settings->m_kias_view_data->m_data_table[ind][QP_NUM_WIDGET].toUInt() - 1);
        }
        m_kia_settings->m_kias_view_data->m_data_table.erase(m_kia_settings->m_kias_view_data->m_data_table.begin() + num_table);
        m_kia_settings->m_kias_view_data->m_data_table_cols.erase(m_kia_settings->m_kias_view_data->m_data_table_cols.begin() + num_table);
        m_kia_settings->m_kias_view_data->m_table_count -= 1;
        emit remove_table(num_table);
        delete ui->lw_list_table->item(num_table);
    }
}

void Kia_constructor::add_graph_to_list(QStringList query_param)
{
    ui->lw_list_graph->addItem("График " + query_param[QP_Y] + " от " + query_param[QP_X]);
}

void Kia_constructor::add_table_to_list(QStringList query_param)
{
    ui->lw_list_table->addItem("Таблица " + query_param[QP_TYPE_ARR] +" №" + QString::number(query_param[QP_NUM_WIDGET].toInt() + 1));
}

void Kia_constructor::on_pb_add_graph_clicked()
{
    m_type_widget = ui->lw_x->currentItem()->text();
    add_graph();
}


void Kia_constructor::on_pb_remove_graph_clicked()
{
    if (ui->lw_list_graph->count() != 0)
    {
        if (ui->lw_list_graph->currentRow() + 1 < ui->lw_list_graph->count())
        {
            for (uint16_t ind = ui->lw_list_graph->currentRow(); ind < m_kia_settings->m_kias_view_data->m_data_graph.size(); ++ind)
                m_kia_settings->m_kias_view_data->m_data_graph[ind][QP_NUM_WIDGET] = QString::number(m_kia_settings->m_kias_view_data->m_data_graph[ind][QP_NUM_WIDGET].toUInt() - 1);
        }
        m_kia_settings->m_kias_view_data->m_data_graph.erase(m_kia_settings->m_kias_view_data->m_data_graph.begin() + ui->lw_list_graph->currentRow());
        m_kia_settings->m_kias_view_data->m_graph_count -= 1;
        emit remove_graph(ui->lw_list_graph->currentRow());
        delete ui->lw_list_graph->currentItem();
    }

}

void Kia_constructor::remove_list()
{
    for (int16_t num_graph = ui->lw_list_graph->count() - 1; num_graph >= 0; num_graph--)
    {
        if (ui->lw_list_graph->count() != 0)
        {
            if (num_graph + 1 < ui->lw_list_graph->count())
            {
                for (uint16_t ind = num_graph; ind < m_kia_settings->m_kias_view_data->m_data_graph.size(); ++ind)
                    m_kia_settings->m_kias_view_data->m_data_graph[ind][QP_NUM_WIDGET] = QString::number(m_kia_settings->m_kias_view_data->m_data_graph[ind][QP_NUM_WIDGET].toUInt() - 1);
            }
            m_kia_settings->m_kias_view_data->m_data_graph.erase(m_kia_settings->m_kias_view_data->m_data_graph.begin() + num_graph);
            m_kia_settings->m_kias_view_data->m_graph_count -= 1;
            emit remove_graph(num_graph);
            delete ui->lw_list_graph->item(num_graph);
        }
    }
    for (int16_t num_table = ui->lw_list_table->count() - 1; num_table >= 0; num_table--)
    {
        if (ui->lw_list_table->count() != 0)
        {
            if (num_table + 1 < ui->lw_list_table->count())
            {
                for (uint16_t ind = num_table; ind < m_kia_settings->m_kias_view_data->m_data_table.size(); ++ind)
                    m_kia_settings->m_kias_view_data->m_data_table[ind][QP_NUM_WIDGET] = QString::number(m_kia_settings->m_kias_view_data->m_data_table[ind][QP_NUM_WIDGET].toUInt() - 1);
            }
            m_kia_settings->m_kias_view_data->m_data_table.erase(m_kia_settings->m_kias_view_data->m_data_table.begin() + num_table);
            m_kia_settings->m_kias_view_data->m_data_table_cols.erase(m_kia_settings->m_kias_view_data->m_data_table_cols.begin() + num_table);
            m_kia_settings->m_kias_view_data->m_table_count -= 1;
            emit remove_table(num_table);
            delete ui->lw_list_table->item(num_table);
        }
    }
}

void Kia_constructor::on_pb_add_table_clicked()
{
    add_table();
}


void Kia_constructor::on_pb_remove_table_clicked()
{
    if (ui->lw_list_table->count() != 0)
    {
        if (ui->lw_list_table->currentRow() + 1 < ui->lw_list_table->count())
        {
            for (uint16_t ind = ui->lw_list_table->currentRow(); ind < m_kia_settings->m_kias_view_data->m_data_table.size(); ++ind)
                m_kia_settings->m_kias_view_data->m_data_table[ind][QP_NUM_WIDGET] = QString::number(m_kia_settings->m_kias_view_data->m_data_table[ind][QP_NUM_WIDGET].toUInt() - 1);
        }
        m_kia_settings->m_kias_view_data->m_data_table.erase(m_kia_settings->m_kias_view_data->m_data_table.begin() + ui->lw_list_table->currentRow());
        m_kia_settings->m_kias_view_data->m_data_table_cols.erase(m_kia_settings->m_kias_view_data->m_data_table_cols.begin() + ui->lw_list_table->currentRow());
        m_kia_settings->m_kias_view_data->m_table_count -= 1;
        emit remove_table(ui->lw_list_table->currentRow());
        delete ui->lw_list_table->currentItem();
    }
}


void Kia_constructor::on_pb_show_graph_clicked()
{
    emit show_graph(ui->lw_list_graph->currentRow());
}

void Kia_constructor::start_thread()
{

    auto dt = QDateTime::fromString(m_kia_settings->m_kias_db->m_experiment_id,"yyyy-MM-dd hh:mm:ss.zzz");
    m_kia_settings->m_kias_db->m_key = QTime(0, 0, 0).msecsTo(dt.time()) / 1000.0;
    m_thread_change_range = std::async([this]()
    {
        m_stop_change_range = true;
        while(m_stop_change_range)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_kia_settings->m_kias_view_data->m_is_change_range)
            {
                m_kia_settings->m_kias_db->m_key = m_kia_settings->m_kias_db->m_key + 1 / 1000.0;
            }
        }
    });
}

