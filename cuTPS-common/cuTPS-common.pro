#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T18:32:47
#
#-------------------------------------------------

TARGET = cutps # will produce libcutps.a
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    Utils.h \
    Entity/BillingInfo.h \
    Entity/Chapter.h \
    Entity/ContentManager.h \
    Entity/Course.h \
    Entity/CreditCardInfo.h \
    Entity/DeliveryInfo.h \
    Entity/Order.h \
    Entity/Section.h \
    Entity/SellableItem.h \
    Entity/ShoppingCart.h \
    Entity/Student.h \
    Entity/Textbook.h \
    Entity/User.h \
    ErrorCodes.h \
    Defines.h \
    Entity/NetMessage.h \
    Entity/NetRequest.h \
    Entity/NetResponse.h

SOURCES += \
    Entity/BillingInfo.cpp \
    Entity/Chapter.cpp \
    Entity/ContentManager.cpp \
    Entity/Course.cpp \
    Entity/CreditCardInfo.cpp \
    Entity/DeliveryInfo.cpp \
    Entity/Order.cpp \
    Entity/Section.cpp \
    Entity/SellableItem.cpp \
    Entity/ShoppingCart.cpp \
    Entity/Student.cpp \
    Entity/Textbook.cpp \
    Entity/User.cpp \
    Entity/NetMessage.cpp \
    Entity/NetRequest.cpp \
    Entity/NetResponse.cpp

macx {
QMAKE_CXXFLAGS += -std=c++0x -stdlib=libc++
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
}

unix:!macx {
QMAKE_CXXFLAGS += -std=c++0x
}
