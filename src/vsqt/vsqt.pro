# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


TEMPLATE = app
TARGET = vsqt
DESTDIR = ../../bin
CONFIG += debug console
LIBS += -L"./../../lib"
DEPENDPATH += .
MOC_DIR += GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += GeneratedFiles
RCC_DIR += GeneratedFiles
include(vsqt.pri)