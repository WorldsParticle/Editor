#-------------------------------------------------
#
# Project created by QtCreator 2016-01-16T18:51:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES +=	source/main.cpp \
                source/mainwindow.cpp \
                source/openglwindow.cpp \
                source/toolwidget.cpp \
    source/bulletworld.cpp

HEADERS  +=	include/mainwindow.hpp \
                include/openglwindow.hpp \
                include/toolwidget.hpp \
    include/bulletworld.h

FORMS    += 	interface/mainwindow.ui \
                interface/toolwidget.ui

CONFIG += c++14

#unix: LIBS += -L/usr/local/lib/ -lEngine
#unix: INCLUDEPATH += -I/usr/local/include/

LIBS += -L$$OUT_PWD/../Engine/build/release/ -lEngine $(pkg-config --libs bullet)
INCLUDEPATH += $$PWD/../Engine/include/ $(pkg-config --cflags bullet)


RESOURCES += \
    ress.qrc


