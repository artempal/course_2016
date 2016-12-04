#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T20:17:18
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = curs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    schedule.cpp \
    createmarks.cpp

HEADERS  += mainwindow.h \
    schedule.h \
    createmarks.h

FORMS    += mainwindow.ui \
    schedule.ui \
    createmarks.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
