#-------------------------------------------------
#
# Project created by QtCreator 2016-01-16T18:51:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES +=  main.cpp        \
    mainwindow.cpp \
    openglwindow.cpp \
    toolwidget.cpp

HEADERS  += \
    mainwindow.hpp \
    openglwindow.hpp \
    toolwidget.hpp

FORMS    += mainwindow.ui \
    toolwidget.ui

CONFIG += c++14
#QMAKE_CXXFLAGS += -std=c++14

unix: LIBS += -L/usr/local/lib/ -lEngine
unix: INCLUDEPATH += -I/usr/local/include/

RESOURCES += \
    ress.qrc
