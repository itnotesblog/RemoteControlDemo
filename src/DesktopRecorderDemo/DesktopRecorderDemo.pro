#-------------------------------------------------
#
# Project created by QtCreator 2016-06-05T12:10:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesktopRecorderDemo
TEMPLATE = app


SOURCES += main.cpp \
    desktoprecorderdemo.cpp

HEADERS  += \
    desktoprecorderdemo.h

FORMS    += \
    desktoprecorderdemo.ui

include( ../../common.pri )
include( ../../app.pri )

LIBS += -lDesktopRecorder$${LIB_SUFFIX}
