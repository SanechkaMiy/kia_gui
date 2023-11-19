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
    ~Kia_main_window();
private:
    CDockAreaWidget* m_window_areas = nullptr;
    CDockAreaWidget* m_graph_areas = nullptr;

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
    uint16_t m_is_start_or_stop = 0;
    void create_main_graph_manager();
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // KIA_MAIN_WINDOW_H
