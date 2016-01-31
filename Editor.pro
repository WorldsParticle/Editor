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
                source/toolwidget.cpp

HEADERS  +=	include/mainwindow.hpp \
                include/openglwindow.hpp \
                include/toolwidget.hpp

FORMS    += 	interface/mainwindow.ui \
                interface/toolwidget.ui

CONFIG += c++14
#QMAKE_CXXFLAGS += -std=c++14

unix: LIBS += -L/usr/local/lib/ -lEngine
unix: INCLUDEPATH += -I/usr/local/include/

RESOURCES += \
    ress.qrc

