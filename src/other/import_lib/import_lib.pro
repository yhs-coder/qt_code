QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form1.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    form1.h \
    widget.h

FORMS += \
    form1.ui \
    widget.ui


win32: LIBS += -L$$PWD/../../lib/ -lopencv_world320

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
