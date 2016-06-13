QT += core gui network

CONFIG += c++11

TARGET = RemoteControlServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    remotecontrolserver.cpp

HEADERS += \
    remotecontrolserver.h \
    ../include/shareddefs.h

include( ../../common.pri )
include( ../../app.pri )

LIBS += -lDesktopRecorder$${LIB_SUFFIX}
LIBS += -L$${LIBS_PATH}/LibQxt/
win32: LIBS += -lQxtCore$${LIB_SUFFIX} -lQxtNetwork$${LIB_SUFFIX}
linux-g++: LIBS += -lQxtCore -lQxtNetwork
linux-g++: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/LibQxt/
