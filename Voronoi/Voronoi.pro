#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T12:12:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = Voronoi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    voronoigenerator.cpp \
    graph.cpp

HEADERS  += mainwindow.h \
    voronoigenerator.h \
    graph.h

FORMS    += mainwindow.ui
