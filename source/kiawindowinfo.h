#ifndef KIAWINDOWINFO_H
#define KIAWINDOWINFO_H

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QTextBrowser>
#include <QLineEdit>
#include <iostream>
#include <QDebug>

namespace Ui {
class KiaWindowInfo;
}

class KiaWindowInfo : public QDialog
{
    Q_OBJECT

public:
    explicit KiaWindowInfo(QWidget *parent = nullptr);
    ~KiaWindowInfo();
public slots:
    void set_info_to_window(QString info);
    void append_info_to_window(QString info);
    void show_context_menu();
private:
    Ui::KiaWindowInfo *ui;
    void create_context_menu();
    QDialog * m_window_options;
    QVBoxLayout* m_layout_for_window_options;
    QLabel* m_label_for_window_options;
    QLineEdit* m_edit_for_window_options;
    QStringList m_font_size;
    QMenu * m_edit_context_menu;
    QHBoxLayout* m_layout_for_place_window_info;
    QTextBrowser* m_text_browser_window_for_info;
    uint32_t m_count_out_to_window = 0;
};

#endif // KIAWINDOWINFO_H
