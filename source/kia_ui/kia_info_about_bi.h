#ifndef KIA_INFO_ABOUT_BI_H
#define KIA_INFO_ABOUT_BI_H

#include <QDialog>

namespace Ui {
class Kia_info_about_bi;
}

class Kia_info_about_bi : public QDialog
{
    Q_OBJECT


public:
    enum STATE
    {
        WO_BI = 0,
        RESTART_KIA = 1,
    };

    explicit Kia_info_about_bi(QWidget *parent = nullptr);
    ~Kia_info_about_bi();
signals:
    void do_state(uint16_t);
private slots:
    void on_pb_cnt_wo_bi_clicked();

    void on_restart_kia_clicked();

private:
    Ui::Kia_info_about_bi *ui;
};

#endif // KIA_INFO_ABOUT_BI_H
