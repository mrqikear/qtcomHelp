#-------------------------------------------------
#
# Project created by QtCreator 2018-04-10T21:55:29
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chuankou
TEMPLATE = app


SOURCES += main.cpp\
        chuan.cpp \
    proto645.cpp \
    debug.cpp

HEADERS  += chuan.h \
    proto645.h \
    define645.h \
    debug.h

FORMS    += chuan.ui

RESOURCES += \
    chuan.qrc
