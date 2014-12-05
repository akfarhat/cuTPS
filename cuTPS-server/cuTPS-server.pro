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
    DatabaseManager.cpp \
    Server.cpp \
    ClientTaskHandling/AddBookTask.cpp \
    ClientTaskHandling/AddCourseTask.cpp \
    ClientTaskHandling/GetBookDetailsTask.cpp \
    ClientTaskHandling/GetRequiredBooksTask.cpp \
    ClientTaskHandling/LoginTask.cpp \
    ClientTaskHandling/SubmitOrderTask.cpp \
    ClientTaskHandling/WorkerTask.cpp \
    ServerNetworking/ServerAsync.cpp \
    ServerNetworking/NetClient.cpp \
    ServerPrefs.cpp \
    ClientTaskHandling/TaskAbsFactory.cpp \
    ClientTaskHandling/LoginTaskFactory.cpp \
    ClientTaskHandling/ContentMgrTaskFactory.cpp \
    ClientTaskHandling/UserTaskFactory.cpp \
    ClientTaskHandling/AdminTaskFactory.cpp \
    ClientTaskHandling/GenerateReportTask.cpp

HEADERS += \
    DatabaseManager.h \
    Server.h \
    ClientTaskHandling/AddBookTask.h \
    ClientTaskHandling/AddCourseTask.h \
    ClientTaskHandling/GetBookDetailsTask.h \
    ClientTaskHandling/GetRequiredBooksTask.h \
    ClientTaskHandling/LoginTask.h \
    ClientTaskHandling/SubmitOrderTask.h \
    ClientTaskHandling/WorkerTask.h \
    ServerNetworking/ServerAsync.h \
    ServerNetworking/NetClient.h \
    ServerPrefs.h \
    ClientTaskHandling/TaskAbsFactory.h \
    ClientTaskHandling/LoginTaskFactory.h \
    ClientTaskHandling/ContentMgrTaskFactory.h \
    ClientTaskHandling/UserTaskFactory.h \
    ClientTaskHandling/AdminTaskFactory.h \
    ClientTaskHandling/GenerateReportTask.h

OTHER_FILES += \
    db/cutpsd.db

macx {
QMAKE_CXXFLAGS += -std=c++0x -stdlib=libc++
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
}

unix:!macx {
QMAKE_CXXFLAGS += -std=c++0x
}

# copy db folder to the build path
copydata.commands = $(COPY_DIR) $$PWD/db $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../cuTPS-common/release/ -lcutps
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../cuTPS-common/debug/ -lcutps
else:unix: LIBS += -L$$OUT_PWD/../cuTPS-common/ -lcutps

INCLUDEPATH += $$PWD/../cuTPS-common
DEPENDPATH += $$PWD/../cuTPS-common
