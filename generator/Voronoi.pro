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
        voronoi/voronoigenerator.cpp \
        voronoi/parabola.cpp \
    voronoi/edge.cpp \
    voronoi/event.cpp \
    generator.cpp \
    map/crossededge.cpp \
    map/zone.cpp \
    map/corner.cpp \
    map/map.cpp \
    map/point.cpp \
    map/halfedge.cpp

HEADERS  += mainwindow.h \
    voronoi/voronoigenerator.h \
    voronoi/parabola.h \
    voronoi/edge.h \
    voronoi/event.h \
    generator.h \
    map/crossededge.h \
    map/zone.h \
    map/corner.h \
    map/map.h \
    map/point.h \
    map/halfedge.h

FORMS    += mainwindow.ui
