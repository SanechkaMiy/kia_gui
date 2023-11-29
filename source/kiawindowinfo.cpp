#include "kiawindowinfo.h"
#include "ui_kiawindowinfo.h"

KiaWindowInfo::KiaWindowInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KiaWindowInfo)
{
    ui->setupUi(this);
    m_layout_for_place_window_info = new QHBoxLayout(this);
    m_text_browser_window_for_info = new QTextBrowser(this);
    m_text_browser_window_for_info->setWordWrapMode(QTextOption::NoWrap);
    m_layout_for_place_window_info->addWidget(m_text_browser_window_for_info);
    create_context_menu();
}

KiaWindowInfo::~KiaWindowInfo()
{
    delete ui;
}

void KiaWindowInfo::set_info_to_window(QString info)
{
    m_text_browser_window_for_info->setText(info);
}

void KiaWindowInfo::append_info_to_window(QString info)
{
        info = info.left(info.lastIndexOf('\n'));
        uint16_t max_count_out_to_window = 50;
        m_count_out_to_window++;
        if (m_count_out_to_window == max_count_out_to_window)
        {
            m_text_browser_window_for_info->clear();
            m_count_out_to_window = 0;
        }
        else
            m_text_browser_window_for_info->append(info);
}

void KiaWindowInfo::show_context_menu()
{
    if(m_edit_context_menu)
        m_edit_context_menu->exec(QCursor::pos());
}

void KiaWindowInfo::create_context_menu()
{
    m_edit_context_menu = m_text_browser_window_for_info->createStandardContextMenu();
    m_edit_context_menu->addAction("Изменить размер шрифта", this, [this]()
    {
        m_window_options->show();
        m_window_options->move(QCursor::pos());
    });
    m_text_browser_window_for_info->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_text_browser_window_for_info, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(show_context_menu()));
    m_window_options = new QDialog(this);
    m_window_options->setWindowTitle("Настройки окна");
    m_label_for_window_options = new QLabel("Размер шрифта", m_window_options);
    m_edit_for_window_options = new QLineEdit(m_window_options);
    m_layout_for_window_options = new QVBoxLayout(m_window_options);
    m_layout_for_window_options->addWidget(m_label_for_window_options);
    m_layout_for_window_options->addWidget(m_edit_for_window_options);
    connect(m_edit_for_window_options, &QLineEdit::returnPressed, [this]()
    {
        auto font_window_info = m_text_browser_window_for_info->font();
        font_window_info.setPointSize(m_edit_for_window_options->text().toInt());
        m_text_browser_window_for_info->setFont(font_window_info);
    });
}


