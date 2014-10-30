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
           Entity/ContentManager.cpp \
           Entity/Course.cpp \
           Entity/DeliveryInfo.cpp \
           Entity/ShoppingCart.cpp \
           Entity/Student.cpp \
           Entity/Textbook.cpp \
           Entity/User.cpp \
           Entity/SellableItem.cpp \
           Entity/BillingInfo.cpp \
           Entity/CreditcardInfo.cpp \
           Entity/Order.cpp \
           Entity/Chapter.cpp \
           Entity/Section.cpp \
           Server/Server.cpp \
           Client/LoginWindow.cpp \
           Client/Tests.cpp \
    Client/ClientNetworkHandler.cpp \
    Server/ServerNetworkHandler.cpp

HEADERS  += Utils.h \
            Entity/ContentManager.h \
            Entity/Course.h \
            Entity/DeliveryInfo.h \
            Entity/ShoppingCart.h \
            Entity/Student.h \
            Entity/Textbook.h \
            Entity/User.h \
            Entity/SellableItem.h \
            Entity/BillingInfo.h \
            Entity/CreditcardInfo.h \
            Entity/Order.h \
            Entity/Chapter.h \
            Entity/Section.h \
            Server/Server.h \
            Client/LoginWindow.h \
            Client/Tests.h \
    Client/ClientNetworkHandler.h \
    Server/ServerNetworkHandler.h

FORMS    += Client/LoginWindow.ui \
            Client/Tests.ui
