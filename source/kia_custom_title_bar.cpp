#include "kia_custom_title_bar.h"

Kia_custom_title_bar::Kia_custom_title_bar(QWidget *parent) :
    QDialog(parent)
{
    auto l = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    setLayout(l);
    l->setSpacing(0);
    l->setContentsMargins(2,2,2,2);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    l->addStretch(1);
    auto* spacer = new QSpacerItem(100, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_close_button = new QPushButton();
    m_close_button->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    m_close_button->setIcon(QIcon(":/icon/Icon/close.png"));
    m_close_button->setIconSize(QSize(16, 16));
    connect(m_close_button, &QPushButton::clicked, this, [this]()
    {
        emit hide_window();
    });
    m_title_layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    m_name_window = new QLabel(this);
    m_title_layout->addWidget(m_name_window);
    m_title_layout->addItem(spacer);
    m_title_layout->addWidget(m_close_button);
    l->addLayout(m_title_layout);
    setMouseTracking(true);
    //
}


void Kia_custom_title_bar::set_movable(bool flag)
{
    m_is_movable = flag;
}

void Kia_custom_title_bar::set_window_title(const QString &title)
{
    m_name_window->setText(title);
}

void Kia_custom_title_bar::mousePressEvent(QMouseEvent *event)
{
    if(m_is_movable && event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_last_pos = event->globalPos();
    }
    else event->ignore();
}

void Kia_custom_title_bar::mouseMoveEvent(QMouseEvent *event)
{
    if(m_is_movable && event->buttons().testFlag(Qt::LeftButton) && m_moving)
    {
        m_curr_pos = event->globalPos() - m_last_pos;
        emit moved(m_curr_pos);
        m_last_pos = event->globalPos();
        emit set_default_pos();
    }
    else event->ignore();
}

void Kia_custom_title_bar::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_is_movable && event->button() == Qt::LeftButton)
    {
        m_moving = false;
        emit moved_if_release();
        m_last_pos = event->globalPos();
    }
    else event->ignore();
}
