#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T18:30:51
#
#-------------------------------------------------

QT       += core network sql
QT       -= gui

TARGET = cutpsd
CONFIG   += console
CONFIG   += -std=gnu++11
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    TPSServerAsync.cpp \
    TPSClient.cpp \
    DatabaseManager.cpp \
    Server.cpp \
    taskhandler/TPSAddBookTask.cpp \
    taskhandler/TPSAddCourseTask.cpp \
    taskhandler/TPSGetBookDetailsTask.cpp \
    taskhandler/TPSGetRequiredBooksTask.cpp \
    taskhandler/TPSLoginTask.cpp \
    taskhandler/TPSSubmitOrderTask.cpp \
    taskhandler/TPSWorkerTask.cpp

HEADERS += \
    TPSServerAsync.h \
    TPSClient.h \
    DatabaseManager.h \
    Server.h \
    taskhandler/TPSAddBookTask.h \
    taskhandler/TPSAddCourseTask.h \
    taskhandler/TPSGetBookDetailsTask.h \
    taskhandler/TPSGetRequiredBooksTask.h \
    taskhandler/TPSLoginTask.h \
    taskhandler/TPSSubmitOrderTask.h \
    taskhandler/TPSWorkerTask.h

macx {
QMAKE_CXXFLAGS += -std=c++0x -stdlib=libc++
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
}

unix:!macx {
QMAKE_CXXFLAGS += -std=c++0x
}

#crap


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
