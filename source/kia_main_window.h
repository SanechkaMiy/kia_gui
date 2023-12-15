#ifndef KIA_MAIN_WINDOW_H
#define KIA_MAIN_WINDOW_H

#include <QMainWindow>
#include <QAction>
#include "Kia_main_struct.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include "DockManager.h"
#include "DockAreaWidget.h"
#include "DockWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "AutoHideTab.h"
#include <QTabWidget>
#include <QTabBar>
#include <QLineEdit>
using namespace ads;

namespace Ui {
class Kia_main_window;
}

class Kia_main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kia_main_window(std::shared_ptr<Kia_settings> kia_settings, QWidget *parent = nullptr);
    void set_widget_on_bottom(QWidget* wgt);
    void set_menu_bar(QMenuBar* menubar);
    CDockManager *create_dock_widget(QWidget* parent);
    uint32_t set_to_dock_widget_status_info(QWidget* wgt, const QString& name_window);
    uint32_t set_to_dock_widget_window_info(QWidget* wgt, const QString& name_window);
    void set_graph_dock_widget();
    void create_action_graph_dock_widget(QMenu* menu);
    void remove_dock_widget(uint16_t num_widget);
    void load_settings_for_tab_widget(uint16_t count_tab_bar);
    ~Kia_main_window();
    QWidget* get_central_dock_widget();
    QWidget* get_current_tab_widget();
    void remove_tab_settings();
signals:
    void remove_graph(uint16_t);
    void remove_table(uint16_t);
    void set_stop();
    void send_to_change_parent(QWidget*);
public slots:
    void set_current_index_tab_widget(uint16_t index);
    void add_tab_bar_slot(QStringList data_tabs);
private:
    void create_main_tab_bar();
    QTabBar* m_tabbar;
    QTabWidget* m_main_tab_widget;
    CDockAreaWidget* m_window_areas = nullptr;
    CDockWidget* m_central_dock_widget;
    uint32_t m_count_doc_widget = -1;
    Ui::Kia_main_window *ui;
    CDockManager* m_dock_manager;
    CDockWidget* m_graph_dock_widget;
    QWidget* m_main_widget;
    QGridLayout* m_main_layout;
    std::shared_ptr<Kia_settings> m_kia_settings;
    QVBoxLayout* m_layout;
    QPushButton* m_start_or_stop;
    QPushButton* m_now;
    QPushButton* m_add_tab;
    uint16_t m_is_start_or_stop = 0;
    void create_main_graph_manager();
    void add_tab_bar();
protected:
    void closeEvent(QCloseEvent *event) override;
    //void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *object, QEvent *event) override;
};

#endif // KIA_MAIN_WINDOW_H
