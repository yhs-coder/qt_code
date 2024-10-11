SOURCES += test.cpp
HEADERS += test.h \
    global.h
TARGET=libdll
TEMPLATE=lib
DEFINES += LIBDLL_LIB
DESTDIR = "$$PWD/../../lib"
DLLDESTDIR = "$$PWD/../../bin"

CONFIG(debug, debug|release) {
    # 如果是debug版本,在库名后加 _d
    TARGET = libdll_d
} else {
    # release版本
    TARGET = libdll
}
message($$TARGET)
# CONFIG += staticlib
#CONFIG += console
