#ifndef KIA_DEBUG_COMMANDS_H
#define KIA_DEBUG_COMMANDS_H

#include <QDialog>
#include <Kia_main_struct.h>
#include "client.h"
namespace Ui {
class Kia_debug_commands;
}

class Kia_debug_commands : public QDialog
{
    Q_OBJECT
struct Struct_Command
{
    uint16_t m_count_direction = 2;
    uint16_t m_count_format = 16;
    uint16_t m_count_sub_address = 32;
    uint16_t m_count_word_data = 32;

};

public:
    explicit Kia_debug_commands(std::shared_ptr<Kia_settings> kia_settings,
                                std::shared_ptr<Client> client, QWidget *parent = nullptr);
    ~Kia_debug_commands();
private slots:
void on_add_command_clicked();

void on_delete_command_clicked();

void on_cb_direction_currentIndexChanged(int index);

void on_cb_word_data_currentIndexChanged(const QString &arg1);

private:
    void add_command();
    Ui::Kia_debug_commands *ui;
    Struct_Command m_struct_commands;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Client> m_client;
};

#endif // KIA_DEBUG_COMMANDS_H
