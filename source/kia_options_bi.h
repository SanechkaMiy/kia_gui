#ifndef KIA_OPTIONS_BI_H
#define KIA_OPTIONS_BI_H

#include "Kia_main_struct.h"
#include "client.h"
#include <QTabWidget>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
namespace Ui {
class Kia_options_bi;
}

class Kia_options_bi : public QWidget
{
    Q_OBJECT

public:
    explicit Kia_options_bi(std::shared_ptr<Kia_settings> kia_settings,
                            std::shared_ptr<Client> client, QWidget *parent = nullptr);
    ~Kia_options_bi();

private:
    Ui::Kia_options_bi *ui;
    void relay_settings();
    void bi_settings();
    void check_state(uint16_t num_relay_command, uint16_t relay_command = 0x0001);
    template <typename Arr>
    void set_data_for_server(qint16 num, Arr& data_arr);
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
    QVBoxLayout* m_layout_for_place_tab_widget;
    std::vector<QVBoxLayout*> m_layout_for_relay_command;
    std::array<QPushButton*, constants::max_count_relay_command> m_pb_relay_command;
    QTabWidget* m_bi_settings;
    std::array<QWidget*, constants::max_count_bi_settings> m_tab_bi_settings;
    QLineEdit* m_ledit_relay_command;
    QLineEdit* m_ledit_relay_pulse_time;
    QLineEdit* m_ledit_relay_polar;
    QCheckBox* m_cb_polar;
};

#endif // KIA_OPTIONS_BI_H
