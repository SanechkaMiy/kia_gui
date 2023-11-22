#ifndef KIA_CUSTOM_TITLE_BAR_H
#define KIA_CUSTOM_TITLE_BAR_H
#include <QDialog>
#include <QPushButton>
#include <QMouseEvent>
#include <QBoxLayout>
#include <QLabel>
class Kia_custom_title_bar : public QDialog
{
    Q_OBJECT
public:
    Kia_custom_title_bar(QWidget* parent = nullptr);
    void set_widget_to_layout(QWidget* wgt);
    void set_movable(bool flag);
private:
    QPushButton* m_close_button;
    QBoxLayout* m_title_layout;
    QPoint m_last_pos;
    QPoint m_curr_pos;
    bool m_is_movable = true;
    bool m_moving;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
signals:
    void moved(QPoint);
    void moved_if_release();
};

#endif // KIA_CUSTOM_TITLE_BAR_H
