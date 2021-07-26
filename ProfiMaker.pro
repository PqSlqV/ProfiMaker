QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dohod.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    rashod.cpp \
    statistik.cpp \
    statistikdohod.cpp

HEADERS += \
    dohod.h \
    mainwindow.h \
    person.h \
    rashod.h \
    statistik.h \
    statistikdohod.h

FORMS += \
    dohod.ui \
    mainwindow.ui \
    rashod.ui \
    statistik.ui \
    statistikdohod.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
