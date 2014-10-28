#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T17:57:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuTPS-KernelPanic
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp\
           Entity/*.cpp

HEADERS  += mainwindow.h\
            Entity/*.h\
            Server/*.h \
    Utils.h

FORMS    += mainwindow.ui
