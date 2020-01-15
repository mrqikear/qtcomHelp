#-------------------------------------------------
#
# Project created by QtCreator 2018-04-10T21:55:29
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
RC_ICONS  =favicon.ico


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chuankou
TEMPLATE = app


SOURCES += main.cpp\
        chuan.cpp \
    debug.cpp \
    proto645.cpp

HEADERS  += chuan.h \
    define645.h \
    debug.h \
    proto645.h

FORMS    += chuan.ui

RESOURCES += \
    chuan.qrc

