#include "kia_profile.h"
#include "ui_kia_profile.h"

Kia_profile::Kia_profile(std::shared_ptr<Kia_settings> kia_settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kia_profile),
    m_kia_settings(kia_settings)
{
    ui->setupUi(this);
}

Kia_profile::~Kia_profile()
{
    delete ui;
}

void Kia_profile::on_add_profile_clicked()
{
    QStringList profile_param;
    profile_param.push_back(ui->lineEdit->text());
    profile_param.push_back(QString::number(m_kia_settings->m_kia_gui_settings->m_count_profile));
    m_kia_settings->m_kia_gui_settings->m_count_profile++;
    m_kia_settings->m_kia_gui_settings->m_list_profile.push_back(profile_param);
    m_kia_settings->m_current_profile = profile_param[NUM_PROFILE].toInt();
    add_profile_slot(profile_param);

}


void Kia_profile::on_delete_profile_clicked()
{
    if (ui->list_profile->currentRow() + 1 < ui->list_profile->count())
        m_kia_settings->m_kia_gui_settings->m_list_profile[ui->list_profile->currentRow() + 1][NUM_PROFILE] = QString::number(m_kia_settings->m_kia_gui_settings->m_list_profile[ui->list_profile->currentRow() + 1][NUM_PROFILE].toUInt() - 1);
    emit remove_action(ui->list_profile->currentRow());
    m_kia_settings->m_kia_gui_settings->m_list_profile.erase(m_kia_settings->m_kia_gui_settings->m_list_profile.begin()
                                                             + ui->list_profile->currentRow());
    m_kia_settings->m_kia_gui_settings->m_count_profile -= 1;
    delete ui->list_profile->currentItem();
}



void Kia_profile::on_select_profile_clicked()
{
    m_kia_settings->m_current_profile = ui->list_profile->currentRow();
}

void Kia_profile::add_profile_slot(QStringList profile_param)
{
    emit create_action(profile_param[NAME_PROFILE], profile_param[NUM_PROFILE].toInt());
    ui->list_profile->addItem(profile_param[NAME_PROFILE]);
}

