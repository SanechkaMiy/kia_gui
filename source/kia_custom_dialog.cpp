#include "kia_custom_dialog.h"

Kia_custom_dialog::Kia_custom_dialog(QWidget *parent) :
    QDialog(parent)
{
    m_main_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    m_main_layout->setSpacing(0);
    m_main_layout->setContentsMargins(2,2,2,2);
    m_custom_title_bar = new Kia_custom_title_bar();
    m_main_layout->addWidget(m_custom_title_bar);
    connect(m_custom_title_bar, SIGNAL(moved(QPoint)), this, SLOT(moved(QPoint)));
    connect(m_custom_title_bar, SIGNAL(moved_if_release()), this, SLOT(moved_if_release()));
    connect(m_custom_title_bar, SIGNAL(set_default_pos()), this, SLOT(set_default_pos_slot()));
    connect(m_custom_title_bar, SIGNAL(hide_window()), this, SLOT(hide_widget()));
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    move(0, 0);
    resize(500, 500);
    setStyleSheet("Kia_custom_dialog{border:1px solid gray}");
}

void Kia_custom_dialog::set_wiget_to_layout(QWidget *wgt)
{
    m_main_layout->addWidget(wgt);
}

void Kia_custom_dialog::set_window_title(const QString &title)
{
    m_custom_title_bar->set_window_title(title);
}

void Kia_custom_dialog::moved(QPoint pos_cur)
{
    m_curr_pos = pos() + pos_cur;
    move(m_curr_pos);
}

void Kia_custom_dialog::moved_if_release()
{
    auto curr_pos = QPoint((int)(m_curr_pos.x() / constants::max_grid_size)
                           * constants::max_grid_size + m_shift,
                           (int)(m_curr_pos.y() / constants::max_grid_size)
                           * constants::max_grid_size + m_shift);
    move(curr_pos);
}

void Kia_custom_dialog::set_default_pos_slot()
{
    startPos = default_pos;
    setCursor(Qt::ArrowCursor);
}

void Kia_custom_dialog::hide_widget()
{
    hide();
    emit set_new_parent();
}

void Kia_custom_dialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragStartPosition = event->pos();
        dragStartGeometry = geometry();
    }
}

void Kia_custom_dialog::mouseReleaseEvent(QMouseEvent *event)
{
    auto wd = (int)(width() / constants::max_grid_size) * constants::max_grid_size;
    auto hg = (int)(height() / constants::max_grid_size) * constants::max_grid_size;
    resize(wd, hg);
}

void Kia_custom_dialog::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
    {
        // No drag, just change the cursor and return

        if (event->x() <= 3 && event->y() <= 3)
        {
            startPos = topleft;
            setCursor(Qt::SizeFDiagCursor);
        } else if (event->x() <= 3 && event->y() >= height() - 3)
        {
            startPos = bottomleft;
            setCursor(Qt::SizeBDiagCursor);
        } else if (event->x() >= width() - 3 && event->y() <= 3)
        {
            startPos = topright;
            setCursor(Qt::SizeBDiagCursor);
        } else if (event->x() >= width() - 3 && event->y() >= height() - 3) {
            startPos = bottomright;
            setCursor(Qt::SizeFDiagCursor);
        } else if (event->x() <= 3) {
            startPos = left;
            setCursor(Qt::SizeHorCursor);
        }
        else if (event->x() >= width() - 3)
        {
            startPos = right;
            setCursor(Qt::SizeHorCursor);
        }
        else if (event->y() <= 3)
        {
            startPos = top;
            setCursor(Qt::SizeVerCursor);
        }
        else if (event->y() >= height() - 3)
        {
            startPos = bottom;
            setCursor(Qt::SizeVerCursor);
        }
        else
        {
            startPos = default_pos;
            setCursor(Qt::ArrowCursor);
        }
        return;
    }
    uint16_t value = 100;
    switch (startPos)
    {
    case topleft:
        if (dragStartGeometry.width() + (dragStartPosition.x() - event->x()) >= value &&
                height() + (dragStartPosition.y() - event->y()) >= value)
        {
            setGeometry(dragStartGeometry.left() - (dragStartPosition.x() - event->x()),
                        dragStartGeometry.top() - (dragStartPosition.y() - event->y()),
                        dragStartGeometry.width() + (dragStartPosition.x() - event->x()),
                        height() + (dragStartPosition.y() - event->y()));
            dragStartGeometry = geometry();
        }
        break;

    case bottomleft:
        if (dragStartGeometry.width() + (dragStartPosition.x() - event->x()) >= value &&
                event->y() >= value)
        {
            setGeometry(dragStartGeometry.left() - (dragStartPosition.x() - event->x()),
                        dragStartGeometry.top(),
                        dragStartGeometry.width() + (dragStartPosition.x() - event->x()),
                        event->y());
            dragStartGeometry = geometry();
        }
        break;

    case topright:
        if (height() + (dragStartPosition.y() - event->y()) >= value &&
                event->x() >= value)
        {
            setGeometry(dragStartGeometry.left(),
                        dragStartGeometry.top() - (dragStartPosition.y() - event->y()),
                        event->x(),
                        height() + (dragStartPosition.y() - event->y()));
            dragStartGeometry = geometry();
        }
        break;

    case bottomright:
        if (event->y() >= value&&
                event->x() >= value)
        {
            setGeometry(dragStartGeometry.left(),
                        dragStartGeometry.top(),
                        event->x(),
                        event->y());
        }
        break;

    case left:
        if (dragStartGeometry.width() + (dragStartPosition.x() - event->x()) >= value&&
                height() >= value)
        {
            setGeometry(dragStartGeometry.left() - (dragStartPosition.x() - event->x()),
                        dragStartGeometry.top(),
                        dragStartGeometry.width() + (dragStartPosition.x() - event->x()),
                        height());
            dragStartGeometry = geometry();
        }
        break;

    case right:
        if (event->x() >= value &&
                height() >= value)
        {
            setGeometry(dragStartGeometry.left(),
                        dragStartGeometry.top(),
                        event->x(),
                        height());
        }
        break;

    case top:
        if (dragStartGeometry.width() >= value &&
                height() + (dragStartPosition.y() - event->y()) >= value)
        {
            setGeometry(dragStartGeometry.left(),
                        dragStartGeometry.top() - (dragStartPosition.y() - event->y()),
                        dragStartGeometry.width(),
                        height() + (dragStartPosition.y() - event->y()));
            dragStartGeometry = geometry();
        }
        break;

    case bottom:
        if (width() >= value &&
                event->y() >= value)
        {
            setGeometry(dragStartGeometry.left(),
                        dragStartGeometry.top(),
                        width(),
                        event->y());
        }
        break;

    default:
        break;
    }
}
