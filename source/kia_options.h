#ifndef KIA_OPTIONS_H
#define KIA_OPTIONS_H

#include <QDialog>
#include <QLabel>
#include <QTabBar>
#include "Kia_main_struct.h"
#include <QVBoxLayout>
#include <QTabWidget>
namespace Ui {
class Kia_options;
}

class Kia_options : public QDialog
{
    Q_OBJECT

public:
    explicit Kia_options(std::shared_ptr<Kia_settings> kia_settings,
                         std::vector<std::pair<QWidget*, QString>> kia_options_list,
                         QWidget *parent = nullptr);
    ~Kia_options();

private:
    Ui::Kia_options *ui;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::vector<std::pair<QWidget*, QString>> m_kia_options_list;
    QVBoxLayout* m_layout_for_place_tab_widget;
    QTabWidget* m_tabs_options;
    std::vector<QVBoxLayout*> m_layout_for_place_options_tab_widget;
};

#endif // KIA_OPTIONS_H
