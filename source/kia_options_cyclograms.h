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
signals:
    void set_mpi_command_for_cyclogram();
private:
    Ui::Kia_options_cyclograms *ui;
    template <typename Arr>
    void set_data_for_server(qint16 num, Arr& data_arr);
    void ai_settings();
    void regular_settings();
    void technical_run_settings();
    void zkr_settings();
    void frames_settings();
    QVBoxLayout* m_layout_for_place_tab_widget;
    std::vector<QVBoxLayout*> m_layout_for_place_cyclogram_tab_widget;
    std::vector<QLineEdit*> m_le_zkr_settings;
    std::vector<QLineEdit*> m_le_full_frames_settings;
    std::vector<QLineEdit*> m_le_technical_run_settings;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    QTabWidget* m_cyclogram_settings;
    std::array<QWidget*, constants::max_count_cyclograms> m_tab_cyclograms;
    std::array<QCheckBox*, constants::max_mpi_command> m_check_box_select_mpi_command;
    QCheckBox* m_check_box_continue_if_fails;
};

#endif // KIA_OPTIONS_CYCLOGRAMS_H
