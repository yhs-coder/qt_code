QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 使用关键区别不同的平台
# win32: TARGET = winmkspecs
# linux:TARGET = linuxmkspecs
# message($$TARGET)

# 使用$$QMAKESPEC来识别当前的平台（系统）和使用的编译器

message($$QMAKESPEC)

# 使用条件判断关键字来实现跨平台编译项目
win32 {
    message(win32)
}
linux {
    message(linux)
}

win32-g++ {
    message(use win32-g++)
}

win32-msvc {
   message(use win32-msvc)
}

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
