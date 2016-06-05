#-------------------------------------------------
#
# Project created by QtCreator 2016-06-05T11:58:26
#
#-------------------------------------------------

include( ../../common.pri )
include( ../../lib.pri )

TARGET = DesktopRecorder$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += DESKTOPRECORDER_LIBRARY

SOURCES += desktoprecorder.cpp

HEADERS += ../include/desktoprecorder.h\
        ../include/desktoprecorder_global.h

linux-g++: LIBS += -lX11 -lXfixes
win32: LIBS += -lUser32 -lGdi32
