#-------------------------------------------------
#
# Project created by QtCreator 2016-01-16T18:51:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES +=  main.cpp        \
            MainWindow.cpp \
    OpenGLWindow.cpp

HEADERS  += MainWindow.hpp \
    OpenGLWindow.hpp

FORMS    += mainwindow.ui

unix: LIBS += -L/usr/local/lib/ -lEngine
unix: INCLUDEPATH += -I/usr/local/include/
