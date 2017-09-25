#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T16:44:31
#
#-------------------------------------------------



QT       += core gui
QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyMusic_2_0
TEMPLATE = app

RC_FILE += Icon.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    mylrc_form.cpp

HEADERS  += mainwindow.h \
    mylrc_form.h \
    header.h

FORMS    += mainwindow.ui \
    mylrc_form.ui

RESOURCES += \
    images.qrc

DISTFILES +=
