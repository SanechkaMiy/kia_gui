#ifndef KIA_CUSTOM_DIALOG_H
#define KIA_CUSTOM_DIALOG_H

#include <QDialog>
#include <QBoxLayout>
#include <QResizeEvent>
#include "kia_custom_title_bar.h"
#include "Kia_main_struct.h"
#include <iostream>

class Kia_custom_dialog : public QDialog
{
    Q_OBJECT
    enum startPositions {topleft, left, bottomleft, bottom, bottomright, right, topright, top, default_pos} startPositions;
public:
    Kia_custom_dialog(QWidget* parent = nullptr);
    void set_wiget_to_layout(QWidget *wgt);
    void set_window_title(const QString& title);
public slots:
    void moved(QPoint pos_cur);
    void moved_if_release();
    void set_default_pos_slot();
    void hide_widget();
private:
    QBoxLayout* m_main_layout;
    Kia_custom_title_bar* m_custom_title_bar;
    QPoint m_curr_pos;
    QRect dragStartGeometry;
    QPoint dragStartPosition;
    enum startPositions startPos;
    int16_t m_shift = 0;
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // KIA_CUSTOM_DIALOG_H
