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
    tools/simplexnoise.cpp \
    generationstep.cpp \
    voronoi/voronoi.cpp \
    elevator.cpp \
    shaper.cpp \
    riveror.cpp \
    moistor.cpp \
    biomizator.cpp \
    heightmap.cpp \
    zonelookup.cpp

HEADERS  += mainwindow.hpp \
    voronoi/parabola.hpp \
    voronoi/edge.hpp \
    voronoi/event.hpp \
    generator.hpp \
    map/crossededge.hpp \
    map/zone.hpp \
    map/corner.hpp \
    map/map.hpp \
    map/point.hpp \
    map/halfedge.hpp \
    map/heightpoint.hpp \
    tools/simplexnoise.hpp \
    tools/nanoflann.hpp \
    tools/bitmap_image.hpp \
    generationstep.hpp \
    voronoi/voronoi.hpp \
    elevator.hpp \
    shaper.hpp \
    riveror.hpp \
    moistor.hpp \
    biomizator.hpp \
    heightmap.hpp \
    zonelookup.hpp

FORMS    += mainwindow.ui
