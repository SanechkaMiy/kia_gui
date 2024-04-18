#include "kia_info_about_bi.h"
#include "ui_kia_info_about_bi.h"
#include <QApplication>
#include <QDesktopWidget>
Kia_info_about_bi::Kia_info_about_bi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kia_info_about_bi)
{
    ui->setupUi(this);
    setModal(true);
    setWindowTitle("Статус БИ");
    QRect scr = QApplication::desktop()->screenGeometry();
    move( scr.center() - rect().center() );
}

Kia_info_about_bi::~Kia_info_about_bi()
{
    delete ui;
}

void Kia_info_about_bi::on_pb_cnt_wo_bi_clicked()
{
    emit do_state(WO_BI);
}


void Kia_info_about_bi::on_restart_kia_clicked()
{
    emit do_state(RESTART_KIA);
}

