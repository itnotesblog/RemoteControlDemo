#-------------------------------------------------
#
# Project created by QtCreator 2016-06-12T09:06:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteControlClient
TEMPLATE = app


SOURCES += main.cpp \
    remotecontrolclientwidget.cpp

HEADERS  +=\
    ../include/shareddefs.h \
    remotecontrolclientwidget.h

include( ../../common.pri )
include( ../../app.pri )

LIBS += -L$${LIBS_PATH}/LibQxt/
win32: LIBS += -lQxtCore$${LIB_SUFFIX} -lQxtNetwork$${LIB_SUFFIX}
linux-g++: LIBS += -lQxtCore -lQxtNetwork

linux-g++: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/LibQxt/

FORMS += \
    remotecontrolclientwidget.ui
