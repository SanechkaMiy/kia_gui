#include "kia_options_frame.h"
#include "ui_kia_options_frame.h"

Kia_options_frame::Kia_options_frame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kia_options_frame)
{
    ui->setupUi(this);
}

Kia_options_frame::~Kia_options_frame()
{
    delete ui;
}
