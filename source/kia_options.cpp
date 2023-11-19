#include "kia_options.h"
#include "ui_kia_options.h"

Kia_options::Kia_options(std::shared_ptr<Kia_settings> kia_settings, std::vector<std::pair<QWidget*, QString>> kia_options_list, QWidget *parent) :
    QDialog(parent)
  , ui(new Ui::Kia_options)
  , m_kia_settings(kia_settings)
  , m_kia_options_list(kia_options_list)
{
    ui->setupUi(this);
    m_layout_for_place_tab_widget = new QVBoxLayout(this);
    m_tabs_options = new QTabWidget(this);
    m_layout_for_place_tab_widget->addWidget(m_tabs_options);
    for (uint16_t num_widget = 0; num_widget < kia_options_list.size(); ++num_widget)
    {
        m_tabs_options->addTab(kia_options_list[num_widget].first, "");
    }
    QTabBar *tabbar = m_tabs_options->tabBar();
    m_tabs_options->setTabPosition(QTabWidget::West);
    for (uint16_t num_widget = 0; num_widget < kia_options_list.size(); ++num_widget)
    {
        tabbar->setTabButton(num_widget, QTabBar::LeftSide, new QLabel(kia_options_list[num_widget].second));
        //m_layout_for_place_options_tab_widget.push_back(new QVBoxLayout(kia_options_list[num_widget]));
    }
    //    QTabWidget* tab = ui->tabWidget;
    //    tab->setTabText(0, "");
    //    tab->setTabText(1, "");

    //    tab->addTab(new QWidget(), "test");


    //    QLabel *lbl1 = new QLabel();
    //    lbl1->setText("tab 1");
    //    tabbar->setTabButton(2, QTabBar::LeftSide, lbl1);
    //    QLabel *lbl2 = new QLabel();
    //    lbl2->setText("tab 2");
    //    tabbar->setTabButton(1, QTabBar::LeftSide, lbl2);
}

Kia_options::~Kia_options()
{
    delete ui;
}
