#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T18:30:51
#
#-------------------------------------------------

QT       += core network sql
QT       -= gui

TARGET = cutpsd
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    TPSServerAsync.cpp \
    TPSClient.cpp \
    TPSWorkerTask.cpp \
    DatabaseManager.cpp \
    ServerNetworkHandler.cpp \
    Server.cpp \
    TPSLoginTask.cpp \
    TPSAddBookTask.cpp

HEADERS += \
    TPSServerAsync.h \
    TPSClient.h \
    TPSWorkerTask.h \
    DatabaseManager.h \
    ServerNetworkHandler.h \
    Server.h \
    TPSLoginTask.h \
    TPSAddBookTask.h

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
