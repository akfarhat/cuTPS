#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T18:30:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuTPS-client
TEMPLATE = app

CONFIG   += -std=gnu++11

SOURCES += main.cpp \
    ClientNetworkHandler.cpp \
    Tests.cpp \
    AddBookControl.cpp \
    AddCourseControl.cpp \
    SubmitOrderControl.cpp \
    ViewBookDetailsControl.cpp \
    ViewRequiredBooksControl.cpp \
    LoginControl.cpp \
    Login.cpp \
    ContentManagementInterface.cpp \
    ManageContentListWindow.cpp \
    ManageContentControl.cpp \
    StudentMainMenuWindow.cpp \
    ViewCartOption.cpp \
    ViewRequiredBooksOption.cpp

HEADERS  += \
    ClientNetworkHandler.h \
    LoginWindow.h \
    Tests.h \
    AddBookControl.h \
    AddCourseControl.h \
    SubmitOrderControl.h \
    ViewBookDetailsControl.h \
    ViewRequiredBooksControl.h \
    LoginControl.h \
    Login.h \
    ContentManagementInterface.h \
    ManageContentListWindow.h \
    ManageContentControl.h \
    StudentMainMenuWindow.h \
    ViewCartOption.h \
    ViewRequiredBooksOption.h

FORMS    += \
    Tests.ui \
    Login.ui \
    ContentManagementInterface.ui \
    ManageContentListWindow.ui \
    StudentMainMenuWindow.ui \
    ViewCartOption.ui \
    ViewRequiredBooksOption.ui

macx {
QMAKE_CXXFLAGS += -std=c++0x -stdlib=libc++
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
}

unix:!macx {
QMAKE_CXXFLAGS += -std=c++0x
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../cuTPS-common/release/ -lcutps
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../cuTPS-common/debug/ -lcutps
else:unix: LIBS += -L$$OUT_PWD/../cuTPS-common/ -lcutps

INCLUDEPATH += $$PWD/../cuTPS-common
DEPENDPATH += $$PWD/../cuTPS-common

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../cuTPS-common/release/libcutps.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../cuTPS-common/debug/libcutps.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../cuTPS-common/release/cutps.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../cuTPS-common/debug/cutps.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../cuTPS-common/libcutps.a
