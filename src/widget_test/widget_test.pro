# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ----------------------------------------------------
QT += core gui  widgets

TEMPLATE = app
TARGET = widget_test
DESTDIR = ../x64/Debug
CONFIG += debug console
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += GeneratedFiles
RCC_DIR += GeneratedFiles
include(widget_test.pri)

FORMS += \
    winstate.ui

HEADERS += \
    winstate.h

SOURCES += \
    winstate.cpp
