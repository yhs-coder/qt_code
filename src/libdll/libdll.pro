SOURCES += test.cpp
HEADERS += test.h \
    global.h
TARGET=libdll
TEMPLATE=lib
DEFINES += LIBDLL_LIB
DESTDIR = "$$PWD/../../bin"
DLLDESTDIR = "$$PWD/../../bin"

# CONFIG += staticlib
# CONFIG += console
