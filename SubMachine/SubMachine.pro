#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T15:08:24
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SubMachine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    air_condition.cpp \
    controll_client.cpp \
    hotel_controll.cpp \
    hotel_room.cpp \
    room.cpp \
    secondary_ac.cpp \
    socket_client.cpp

HEADERS  += mainwindow.h \
    air_condition.h \
    controll_client.h \
    hotel_controll.h \
    hotel_room.h \
    room.h \
    secondary_ac.h \
    socket_client.h

FORMS    += mainwindow.ui
