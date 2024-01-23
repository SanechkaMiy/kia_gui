#include "kia_main_window.h"
#include "ui_kia_main_window.h"

Kia_main_window::Kia_main_window(std::shared_ptr<Kia_settings> kia_settings, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Kia_main_window),
    m_kia_settings(kia_settings)
{
    ui->setupUi(this);
    qApp->installEventFilter( this );
    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    CDockManager::setAutoHideConfigFlags(CDockManager::DefaultAutoHideConfig);
    m_main_tab_widget = new QTabWidget(this);
    m_main_tab_widget->setTabPosition(QTabWidget::South);
    m_main_tab_widget->setMovable(true);
    m_tabbar = m_main_tab_widget->tabBar();
    m_main_widget = new QWidget();
    m_main_layout = new QGridLayout(m_main_widget);
    connect(m_main_tab_widget, &QTabWidget::currentChanged, this, [this](int index)
    {
        m_kia_settings->m_kia_gui_settings->m_current_main_tab_widget = index;
    });

    connect(m_main_tab_widget, &QTabWidget::tabBarDoubleClicked, this, [this](int index)
    {
        if (index != 0)
        {
            auto new_index = index - 1;
            if (new_index + 1 < (m_main_tab_widget->count() - 1))
            {
                for (uint16_t ind = new_index; ind < m_kia_settings->m_kia_gui_settings->m_data_tabs.size(); ++ind)
                {
                    m_kia_settings->m_kia_gui_settings->m_data_tabs[ind][NUM_TAB] = QString::number(m_kia_settings->m_kia_gui_settings->m_data_tabs[ind][NUM_TAB].toUInt() - 1);

                }
            }
            for (auto i = m_kia_settings->m_kia_gui_settings->m_current_num_parent.cbegin(), end = m_kia_settings->m_kia_gui_settings->m_current_num_parent.cend(); i != end; ++i)
            {
                if (index == i.value())
                    emit send_to_change_parent(i.key());
            }
            if (index + 1 < m_main_tab_widget->count())
            {
                for (auto i = m_kia_settings->m_kia_gui_settings->m_current_num_parent.cbegin(), end = m_kia_settings->m_kia_gui_settings->m_current_num_parent.cend(); i != end; ++i)
                    if ((index + 1) == i.value())
                        m_kia_settings->m_kia_gui_settings->m_current_num_parent[i.key()] = m_kia_settings->m_kia_gui_settings->m_current_num_parent[i.key()] - 1;
            }
            m_kia_settings->m_kia_gui_settings->m_data_tabs.erase(m_kia_settings->m_kia_gui_settings->m_data_tabs.begin() + new_index);
            m_main_tab_widget->removeTab(index);
            delete m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[index];
            m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets.erase(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets.begin() + index);
            m_kia_settings->m_kia_gui_settings->m_count_tab_bar--;
        }

    });

    m_add_tab = new QPushButton("+", this);
    m_add_tab->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    m_add_tab->resize(2, 2);
    m_main_tab_widget->setCornerWidget(m_add_tab, Qt::Corner::TopLeftCorner);
    create_main_tab_bar();
    connect(m_add_tab, &QPushButton::clicked, this, [this]()
    {
        add_tab_bar();
    });
    create_main_graph_manager();
}


void Kia_main_window::set_widget_on_bottom(QWidget* wgt)
{
    m_main_layout->setSpacing(0);
    m_main_layout->setContentsMargins(0,0,0,0);
    auto* spacer = new QSpacerItem(20, 40, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_main_layout->addItem(spacer, 0, 0);
    m_main_layout->addWidget(wgt, 1, 0);
    m_main_layout->addLayout(m_layout, 1, 1);
}

void Kia_main_window::set_menu_bar(QMenuBar *menubar)
{
    ui->menubar->addActions(menubar->actions());
}

CDockManager* Kia_main_window::create_dock_widget(QWidget *parent)
{
    m_dock_manager = new CDockManager(parent);
    m_central_dock_widget = new CDockWidget("CentralWidget");
    m_central_dock_widget->setWidget(m_main_tab_widget);
    //m_main_tab_widget->addTab(m_central_dock_widget, "centr");
    auto* central_dock_area = m_dock_manager->setCentralWidget(m_central_dock_widget);
    central_dock_area->setAllowedAreas(DockWidgetArea::OuterDockAreas);
    m_window_areas = nullptr;
    set_graph_dock_widget();
    return m_dock_manager;
}

uint32_t Kia_main_window::set_to_dock_widget_status_info(QWidget *wgt, const QString &name_window)
{
    m_count_doc_widget++;
    m_kia_settings->m_kia_gui_settings->m_dock_widget.push_back(new CDockWidget(name_window));
    m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget]->setWidget(wgt);
    m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget]->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromContent);

    if (m_count_doc_widget == 0)
        //m_dock_manager->addAutoHideDockWidget(SideBarLocation::SideBarLeft, m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget]);
        m_window_areas = m_dock_manager->addDockWidget(DockWidgetArea::LeftDockWidgetArea,  m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget], m_window_areas);
    else
        //m_dock_manager->addAutoHideDockWidget(SideBarLocation::SideBarBottom, m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget]);
        m_dock_manager->addDockWidget(DockWidgetArea::BottomDockWidgetArea,  m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget], m_window_areas);

    return m_count_doc_widget;
}

uint32_t Kia_main_window::set_to_dock_widget_window_info(QWidget *wgt, const QString &name_window)
{
    m_count_doc_widget++;
    m_kia_settings->m_kia_gui_settings->m_dock_widget.push_back(new CDockWidget(name_window));
    m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget]->setWidget(wgt);
    m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget]->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromContent);
    m_window_areas = m_dock_manager->addDockWidget(DockWidgetArea::LeftDockWidgetArea,  m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget], m_window_areas);
    m_kia_settings->m_kia_gui_settings->m_dock_widget[m_count_doc_widget]->toggleView(false);
    return m_count_doc_widget;
}

void Kia_main_window::set_graph_dock_widget()
{
    m_graph_dock_widget = new CDockWidget("Ось времени");
    m_graph_dock_widget->setWidget(m_main_widget);
    m_dock_manager->addDockWidget(DockWidgetArea::BottomDockWidgetArea,  m_graph_dock_widget);
}

void Kia_main_window::create_action_graph_dock_widget(QMenu *menu)
{
    auto action = menu->addAction("Ось времени");
    m_graph_dock_widget->setToggleViewAction(action);
}

void Kia_main_window::remove_dock_widget(uint16_t num_widget)
{
    m_count_doc_widget--;
    m_kia_settings->m_kia_gui_settings->m_dock_widget[num_widget]->deleteDockWidget();
    m_kia_settings->m_kia_gui_settings->m_dock_widget.erase(m_kia_settings->m_kia_gui_settings->m_dock_widget.begin() + num_widget);
}

void Kia_main_window::load_settings_for_tab_widget(uint16_t count_tab_bar)
{
    for (uint16_t num_bar = 0; num_bar < count_tab_bar; ++num_bar)
        add_tab_bar();
}

Kia_main_window::~Kia_main_window()
{
    delete ui;
}

QWidget* Kia_main_window::get_central_dock_widget()
{
    return m_main_tab_widget;
}

QWidget *Kia_main_window::get_current_tab_widget()
{
    return m_main_tab_widget->currentWidget();
}

void Kia_main_window::remove_tab_settings()
{
    //std::cout << m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets.size() << std::endl;
    for (int16_t index = m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets.size() - 1; index >= 0; index--)
    {

        if (index > 0)
        {
            auto new_index = index - 1;
            if (new_index + 1 < (m_main_tab_widget->count() - 1))
            {
                for (uint16_t ind = new_index; ind < m_kia_settings->m_kia_gui_settings->m_data_tabs.size(); ++ind)
                    m_kia_settings->m_kia_gui_settings->m_data_tabs[ind][NUM_TAB] = QString::number(m_kia_settings->m_kia_gui_settings->m_data_tabs[ind][NUM_TAB].toUInt() - 1);
            }

            for (auto i = m_kia_settings->m_kia_gui_settings->m_current_num_parent.cbegin(), end = m_kia_settings->m_kia_gui_settings->m_current_num_parent.cend(); i != end; ++i)
            {
                if (index == i.value())
                {
                    emit send_to_change_parent(i.key());
                }
            }
            if (index + 1 < m_main_tab_widget->count())
                for (auto i = m_kia_settings->m_kia_gui_settings->m_current_num_parent.cbegin(), end = m_kia_settings->m_kia_gui_settings->m_current_num_parent.cend(); i != end; ++i)
                    if ((index + 1) == i.value())
                        m_kia_settings->m_kia_gui_settings->m_current_num_parent[i.key()] = m_kia_settings->m_kia_gui_settings->m_current_num_parent[i.key()] - 1;


            m_kia_settings->m_kia_gui_settings->m_data_tabs.erase(m_kia_settings->m_kia_gui_settings->m_data_tabs.begin() + new_index);
            m_main_tab_widget->removeTab(index);
            delete m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[index];
            m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets.erase(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets.begin() + index);
            m_kia_settings->m_kia_gui_settings->m_count_tab_bar--;
        }
    }
}

void Kia_main_window::set_current_index_tab_widget(uint16_t index)
{
    m_main_tab_widget->setCurrentIndex(index);
}

void Kia_main_window::add_tab_bar_slot(QStringList data_tabs)
{
    m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets.push_back(new QWidget(this));
    m_main_tab_widget->addTab(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[data_tabs[NUM_TAB].toInt() + 1], data_tabs[NAME_TAB]);
    m_true_num_tabs[data_tabs[NAME_TAB]] = data_tabs[NUM_TAB].toInt() + 1;
    //m_tabbar->setTabButton(m_kia_settings->m_kia_gui_settings->m_count_tab_bar + 1, QTabBar::RightSide, new QLineEdit("hello", this));
}

void Kia_main_window::create_main_tab_bar()
{
    m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets.push_back(new QWidget(this));
    m_main_tab_widget->addTab(m_kia_settings->m_kia_gui_settings->m_main_tabs_widgets[0], "Главная");
}

void Kia_main_window::create_main_graph_manager()
{
    m_layout = new QVBoxLayout();
    m_start_or_stop = new QPushButton();
    m_start_or_stop->setIcon(QIcon(":/icon/Icon/pause.png"));
    m_start_or_stop->setIconSize(QSize(16, 16));
    connect(m_start_or_stop, &QPushButton::clicked, this, [this]()
    {
        m_is_start_or_stop = (m_is_start_or_stop + 1) % 2;
        QIcon icon;
        if (m_is_start_or_stop != 0)
        {
            m_kia_settings->m_kias_view_data->m_is_stop_graph = false;
            m_kia_settings->m_kias_view_data->m_is_change_range = false;
            m_start_or_stop->setIcon(QIcon(":/icon/Icon/play.png"));
            m_start_or_stop->setIconSize(QSize(16, 16));
        }
        else
        {
            m_kia_settings->m_kias_view_data->m_is_stop_graph = true;
            m_kia_settings->m_kias_view_data->m_is_change_range = true;
            QIcon icon(":/icon/Icon/play.png");
            m_start_or_stop->setIcon(QIcon(":/icon/Icon/pause.png"));
            m_start_or_stop->setIconSize(QSize(16, 16));
        }

    });
    m_start_or_stop->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    m_layout->addWidget(m_start_or_stop);

    m_now = new QPushButton();
    m_now->setIcon(QIcon(":/icon/Icon/now.png"));
    m_now->setIconSize(QSize(16, 16));

    connect(m_now, &QPushButton::clicked, this, [this]()
    {
        QDateTime current = QDateTime::currentDateTime();
        m_kia_settings->m_kias_db->m_key = QTime(0, 0, 0).msecsTo(current.time()) / 1000.0;
    });
    m_now->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    m_layout->addWidget(m_now);
}

void Kia_main_window::add_tab_bar()
{
    QStringList data_tabs;
    data_tabs.push_back(QString::number(m_kia_settings->m_kia_gui_settings->m_count_tab_bar));
    data_tabs.push_back("Лист №" + QString::number(m_kia_settings->m_kia_gui_settings->m_count_tab_bar + 1));
    add_tab_bar_slot(data_tabs);
    m_kia_settings->m_kia_gui_settings->m_data_tabs.push_back(data_tabs);
    m_kia_settings->m_kia_gui_settings->m_count_tab_bar++;
}

void Kia_main_window::closeEvent(QCloseEvent *event)
{

    Q_UNUSED(event);
    m_kia_settings->m_kia_gui_settings->m_widget_is_closed = true;
}

bool Kia_main_window::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress )
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Space)
        {
            emit set_stop();
            return true;
        }
    }
    return QMainWindow::eventFilter(object, event);
}

