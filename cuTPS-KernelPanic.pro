#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T17:57:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuTPS-KernelPanic
TEMPLATE = app


SOURCES += main.cpp \
           mainwindow.cpp \
           Entity/ContentManager.cpp \
           Entity/Course.cpp \
           Entity/DeliveryInfo.cpp \
           Entity/ShoppingCart.cpp \
           Entity/Student.cpp \
           Entity/Textbook.cpp \
           Entity/User.cpp \
           Entity/SellableItem.cpp

HEADERS  += mainwindow.h \
            Entity/ContentManager.h \
            Entity/Course.h \
            Entity/DeliveryInfo.h \
            Entity/ShoppingCart.h \
            Entity/Student.h \
            Entity/Textbook.h \
            Entity/User.h \
            Entity/SellableItem.h

FORMS    += mainwindow.ui
