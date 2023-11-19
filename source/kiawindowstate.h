#ifndef KIAWINDOWSTATE_H
#define KIAWINDOWSTATE_H
#include <QDialog>
#include <QDebug>
#include <QTableWidget>
#include <QLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <iostream>
#include <QSettings>
#include "Kia_main_struct.h"
#include <thread>
namespace Ui {
class KiaWindowState;
}

class KiaWindowState : public QDialog
{
    Q_OBJECT

public:
    explicit KiaWindowState(std::shared_ptr<Kia_settings> kia_settings, QWidget *parent = nullptr);
    ~KiaWindowState();
    void table_setup(qint16 type_bi);
    QStringList get_row();
public slots:
    void set_width_for_vertical_header(qint16 width_header, qint16 width_col);
    void set_data_to_table_state(qint16 type_bi, QStringList data_from_server);
    void set_status_bi_1s_mark(qint16 num_bi);
    void hide_or_show_row(qint16 index_row, bool state);
    void set_color_row(qint16 index_row, bool state);
private:
    QHBoxLayout* m_layout_for_place_table_state;
    QSettings m_settings;
    std::shared_ptr<Kia_settings> m_kia_settings;
    Ui::KiaWindowState *ui;
    QTableWidget* m_set_table;
    std::vector<std::vector<QLineEdit*>> m_line_edit_data_into_table;
    std::vector<uint16_t> m_count_for_change_color;
    std::vector<Qt::GlobalColor> m_true_color;
    std::vector<bool> m_is_color;
};

#endif // KIAWINDOWSTATE_H
