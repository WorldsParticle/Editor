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
        source/voronoi/parabola.cpp \
    source/voronoi/edge.cpp \
    source/voronoi/event.cpp \
    source/generator.cpp \
    source/map/crossededge.cpp \
    source/map/zone.cpp \
    source/map/corner.cpp \
    source/map/map.cpp \
    source/map/point.cpp \
    source/map/halfedge.cpp \
    source/tools/simplexnoise.cpp \
    source/generationstep.cpp \
    source/voronoi/voronoi.cpp \
    source/elevator.cpp \
    source/shaper.cpp \
    source/riveror.cpp \
    source/moistor.cpp \
    source/biomizator.cpp \
    source/heightmap.cpp \
    source/zonelookup.cpp

HEADERS  += mainwindow.hpp \
    include/voronoi/parabola.hpp \
    include/voronoi/edge.hpp \
    include/voronoi/event.hpp \
    include/generator.hpp \
    include/map/crossededge.hpp \
    include/map/zone.hpp \
    include/map/corner.hpp \
    include/map/map.hpp \
    include/map/point.hpp \
    include/map/halfedge.hpp \
    include/map/heightpoint.hpp \
    include/tools/simplexnoise.hpp \
    include/tools/nanoflann.hpp \
    include/tools/bitmap_image.hpp \
    include/generationstep.hpp \
    include/voronoi/voronoi.hpp \
    include/elevator.hpp \
    include/shaper.hpp \
    include/riveror.hpp \
    include/moistor.hpp \
    include/biomizator.hpp \
    include/heightmap.hpp \
    include/zonelookup.hpp

CONFIG += warn_off
  QMAKE_CXXFLAGS_WARN_OFF =
   QMAKE_CFLAGS_WARN_OFF =
QMAKE_CXXFLAGS += -fPIC -Wctor-dtor-privacy -Wnoexcept -Wnon-virtual-dtor -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wno-pmf-conversions -Wsign-promo -Wdouble-promotion -Wmissing-include-dirs -Wswitch-default -Wfloat-equal -Wzero-as-null-pointer-constant -Wuseless-cast -Wconversion -Wlogical-op -Wmissing-declarations -Winline -Wshadow -Wall -Wextra



FORMS    += mainwindow.ui
