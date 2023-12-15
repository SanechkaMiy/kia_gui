#ifndef KIA_PROFILE_H
#define KIA_PROFILE_H

#include <QDialog>
#include "Kia_main_struct.h"
namespace Ui {
class Kia_profile;
}

class Kia_profile : public QDialog
{
    Q_OBJECT

public:
    explicit Kia_profile(std::shared_ptr<Kia_settings> kia_settings,
                         QWidget *parent = nullptr);
    ~Kia_profile();
        void create_main_profile(const QString& name_profile);
signals:
    void create_action(QString, int32_t);
    void remove_action(int32_t);
private slots:
    void on_add_profile_clicked();

    void on_delete_profile_clicked();

    void on_select_profile_clicked();

    void add_profile_slot(QStringList profile_param);
private:
    Ui::Kia_profile *ui;
    std::shared_ptr<Kia_settings> m_kia_settings;
};

#endif // KIA_PROFILE_H
