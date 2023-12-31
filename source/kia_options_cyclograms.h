#ifndef KIA_OPTIONS_CYCLOGRAMS_H
#define KIA_OPTIONS_CYCLOGRAMS_H

#include <QWidget>
#include <QDialog>
#include <QTabWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include "client.h"
#include <QCheckBox>
#include "Kia_main_struct.h"
namespace Ui {
class Kia_options_cyclograms;
}

class Kia_options_cyclograms : public QWidget
{
    Q_OBJECT

public:
    explicit Kia_options_cyclograms(std::shared_ptr<Kia_settings> kia_settings,
                                    std::shared_ptr<Client> client,
                                    QWidget *parent = nullptr);
    ~Kia_options_cyclograms();
public slots:
    void set_load_settings(qint16 type_load, QStringList load_data);
    void set_load_tp_settings(qint16 type_settings, QStringList load_data);
signals:
    void set_mpi_command_for_cyclogram();
private:
    Ui::Kia_options_cyclograms *ui;
    template <typename Arr>
    void set_data_for_server(qint16 num, Arr& data_arr);
    void ai_settings();
    void regular_settings();
    void cyclogram_settings_if_run_a_lot(std::vector<QLineEdit *> &le_settings, std::array<float, constants::max_count_param> &param, uint16_t type_settings, uint16_t type_to_send);
    void cyclogram_tp();
    void load_for_specific_cyclogram(QStringList load_data, std::vector<QLineEdit *> &le_settings, std::array<float, constants::max_count_param> &param, uint16_t type_to_send);
    QVBoxLayout* m_layout_for_place_tab_widget;
    std::vector<QVBoxLayout*> m_layout_for_place_cyclogram_tab_widget;
    std::vector<QLineEdit*> m_le_zkr_settings;
    std::vector<QLineEdit*> m_le_full_frames_settings;
    std::vector<QLineEdit*> m_le_technical_run_settings;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    QTabWidget* m_cyclogram_settings;
    std::array<QWidget*, constants::max_count_cyclograms> m_tab_cyclograms;
    std::vector<QCheckBox*> m_check_box_select_mpi_command;

    std::vector<QCheckBox*> m_check_box_select_cyclograms_tp;
    std::vector<QCheckBox*> m_check_box_select_cyclograms_ai;
    std::vector<QLineEdit*> m_le_count_to_do_cyclograms;
    QCheckBox* m_check_box_continue_if_fails;
    QCheckBox* m_check_box_off_power_for_tp;
};

#endif // KIA_OPTIONS_CYCLOGRAMS_H
