#-------------------------------------------------
#
# Project created by QtCreator 2011-11-29T15:25:36
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}
#CONFIG += static static-libgcc


TARGET = GrandPrix
TEMPLATE = app

INCLUDEPATH += include
SOURCES += \
    src/main.cpp\
    src/grandprix.cpp \
    src/gpcontrolview.cpp \
    src/gpmapview.cpp \
    src/gpmapselector.cpp \
    src/gpcontrol.cpp \
    src/gpdriverselector.cpp \
    src/finishdialog.cpp \
    src/gpprogression.cpp \
    src/car.cpp \
    src/headless.cpp

HEADERS  += \
    include/grandprix.h \
    include/gpcontrolview.h \
    include/gpmapview.h \
    include/gpmapselector.h \
    include/gpcontrol.h \
    include/gpdriverselector.h \
    include/finishdialog.h \
    include/gpprogression.h \
    include/car.h \
    include/headless.h

FORMS    += \
    ui/grandprix.ui \
    ui/gpcontrolview.ui \
    ui/gpmapview.ui \
    ui/gpmapselector.ui \
    ui/gpdriverselector.ui \
    ui/finishdialog.ui \
    ui/gpprogression.ui

RESOURCES += \
    res.qrc

TRANSLATIONS = GrandPrix_fr_FR.ts GrandPrix_en_EN.ts

OBJECTS_DIR=.obj
MOC_DIR=.moc
UI_DIR=.ui
RCC_DIR=.rcc
