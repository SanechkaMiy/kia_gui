QT       += core gui printsupport sql
QT += KWidgetsAddons
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    client.cpp \
    kia_main_window.cpp \
    kia_options.cpp \
    kia_constructor.cpp \
    kia_db.cpp \
    kia_options_bi.cpp \
    kia_options_command.cpp \
    kia_options_cyclograms.cpp \
    kia_options_interface.cpp \
    kia_plot/kia_graph.cpp \
    kia_plot/kia_graph_manager.cpp \
    kia_plot/qcustomplot.cpp \
    kia_profile.cpp \
    kia_table/kia_table_manager.cpp \
    kia_table/kia_tables.cpp \
    kiacore.cpp \
    kiamenubar.cpp \
    kiawindowinfo.cpp \
    kiawindowiswork.cpp \
    kiawindowsettings.cpp \
    kiawindowstate.cpp \
    main.cpp \
    save_read_settings.cpp

HEADERS += \
    Kia_enums.h \
    Kia_main_struct.h \
    client.h \
    kia_main_window.h \
    kia_options.h \
    kia_constructor.h \
    kia_db.h \
    kia_options_bi.h \
    kia_options_command.h \
    kia_options_cyclograms.h \
    kia_options_interface.h \
    kia_plot/kia_graph.h \
    kia_plot/kia_graph_manager.h \
    kia_plot/qcustomplot.h \
    kia_profile.h \
    kia_table/kia_table_manager.h \
    kia_table/kia_tables.h \
    kiacore.h \
    kiamenubar.h \
    kiawindowinfo.h \
    kiawindowiswork.h \
    kiawindowsettings.h \
    kiawindowstate.h \
    save_read_settings.h

FORMS += \
    kia_main_window.ui \
    kia_options.ui \
    kia_constructor.ui \
    kia_options_bi.ui \
    kia_options_command.ui \
    kia_options_cyclograms.ui \
    kia_options_interface.ui \
    kia_profile.ui \
    kiamenubar.ui \
    kiawindowinfo.ui \
    kiawindowiswork.ui \
    kiawindowsettings.ui \
    kiawindowstate.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../../kia_gui/source/kia_plot
DEPENDPATH += $$PWD/../../kia_gui/source/kia_plot

INCLUDEPATH += $$PWD/../../kia_gui/source/kia_table
DEPENDPATH += $$PWD/../../kia_gui/source/kia_table

RESOURCES += \
    image.qrc

unix:!macx: LIBS += -L$$PWD/../../QtAdvancedDocking/lib/ -lqtadvanceddocking

INCLUDEPATH += $$PWD/../../QtAdvancedDocking/src
DEPENDPATH += $$PWD/../../QtAdvancedDocking/src
