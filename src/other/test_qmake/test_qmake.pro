QT += widgets
message($$PWD)
INCLUDEPATH += $$PWD/../../include

# 导入库
# LIBS += -L../../lib -lopencv_world320
LIBS += -L$$PWD/../../lib/ -lopencv_world320
DESTDIR += $$PWD/../../bin

# 生成的文件名
TARGET = test_qmake

SOURCES += main.cpp 
CONFIG += c++11 console


