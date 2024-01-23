#ifndef KIA_OPTIONS_FRAME_H
#define KIA_OPTIONS_FRAME_H

#include <QWidget>

namespace Ui {
class Kia_options_frame;
}

class Kia_options_frame : public QWidget
{
    Q_OBJECT

public:
    explicit Kia_options_frame(QWidget *parent = nullptr);
    ~Kia_options_frame();

private:
    Ui::Kia_options_frame *ui;
};

#endif // KIA_OPTIONS_FRAME_H
