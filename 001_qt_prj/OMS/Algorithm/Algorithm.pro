#-------------------------------------------------
#
# Project created by QtCreator 2014-12-13T15:05:50
#
#-------------------------------------------------

QT       -= gui

TARGET = Algorithm
TEMPLATE = lib

DEFINES += ALGORITHM_LIBRARY

SOURCES += algorithm.cpp \
    sclist.cpp \
    sfilter.cpp \
    speak.cpp

HEADERS += algorithm.h\
        algorithm_global.h \
    sclist.h \
    sfilter.h \
    speak.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
