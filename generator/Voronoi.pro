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
        voronoi/parabola.cpp \
    voronoi/edge.cpp \
    voronoi/event.cpp \
    generator.cpp \
    map/crossededge.cpp \
    map/zone.cpp \
    map/corner.cpp \
    map/map.cpp \
    map/point.cpp \
    map/halfedge.cpp \
    noise/simplexnoise.cpp \
    generationstep.cpp \
    voronoi/voronoi.cpp \
    elevator.cpp \
    shaper.cpp \
    riveror.cpp \
    moistor.cpp \
    biomizator.cpp \
    heightmap.cpp \
    zonelookup.cpp

HEADERS  += mainwindow.h \
    voronoi/parabola.h \
    voronoi/edge.h \
    voronoi/event.h \
    generator.h \
    map/crossededge.h \
    map/zone.h \
    map/corner.h \
    map/map.h \
    map/point.h \
    map/halfedge.h \
    map/heightpoint.h \
    noise/simplexnoise.h \
    generationstep.h \
    voronoi/voronoi.h \
    elevator.h \
    shaper.h \
    riveror.h \
    moistor.h \
    biomizator.h \
    heightmap.h \
    zonelookup.h \
    nanoflann.h

FORMS    += mainwindow.ui
