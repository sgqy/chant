#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T13:09:45
#
#-------------------------------------------------

QMAKE_EXTRA_TARGETS += customtarget1

customtarget1.target = dummy
customtarget1.commands = set PATH=C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Bin;$(PATH)

PRE_TARGETDEPS += dummy

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chant-gui
TEMPLATE = app


SOURCES += main.cpp\
        chant.cpp \
    base32.c \
    base4096.c

HEADERS  += chant.hpp \
    base32.h \
    base4096.h

FORMS    += chant.ui
CONFIG   += c++11
QMAKE_CFLAGS += -std=c99

RESOURCES += \
    data.qrc
