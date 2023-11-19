#ifndef KIAWINDOWSETTINGS_H
#define KIAWINDOWSETTINGS_H
#include "Kia_main_struct.h"
#include "Kia_enums.h"
#include <QDialog>
#include <QTableWidget>
#include <QLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QHeaderView>
namespace Ui {
class KiaWindowSettings;
}

class KiaWindowSettings : public QDialog
{
    Q_OBJECT
public:
    explicit KiaWindowSettings(std::shared_ptr<Kia_settings> kia_settings, QWidget *parent = nullptr);
    ~KiaWindowSettings();
public slots:
    void create_table_settings(qint16 type_bokz);
    void set_data_table_settings(QStringList data_from_server);
private:
    QHBoxLayout* m_layout_for_place_table_settings;
    std::vector<int> m_mpi_num;
    std::shared_ptr<Kia_settings> m_kia_settings;
    Ui::KiaWindowSettings *ui;
    QTableWidget* m_set_table;
    std::vector<QComboBox*> m_combo_box_address;
    std::vector<QComboBox*> m_combo_box_td;
    std::vector<QComboBox*> m_combo_box_mpi;
    std::vector<QComboBox*> m_combo_box_lpi;
    std::vector<QCheckBox*> m_check_box_used;
    std::vector<QComboBox*> m_cob_used_bi;
    std::vector<QComboBox*> m_cob_num_used_channel;
    template <typename Arr>
    void set_data_for_server(qint16 num, Arr& data_arr);
signals:
    void send_data_from_client(qint16, QStringList);
    void send_value_width_for_state_table(qint16, qint16);
};

#endif // KIAWINDOWSETTINGS_H
