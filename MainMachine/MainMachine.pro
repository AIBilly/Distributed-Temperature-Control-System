#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T15:08:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainMachine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindlg.cpp \
    sign_up.cpp \
    staff_controler.cpp \
    staff_manage.cpp \
    options.cpp \
    Lock.cpp \
    MasterControl.cpp \
    normalcommunicationprocess.cpp \
    readrequireprocess.cpp

HEADERS  += mainwindow.h \
    logindlg.h \
    sign_up.h \
    staff_controler.h \
    staff_manage.h \
    options.h \
    Lock.h \
    MasterControl.h \
    normalcommunicationprocess.h \
    readrequireprocess.h

FORMS    += mainwindow.ui \
    logindlg.ui \
    sign_up.ui \
    staff_manage.ui \
    options.ui

DISTFILES += \
    MainMachine.pro.user
