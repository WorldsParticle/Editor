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
                source/particlewidget.cpp \
                source/modelwidget.cpp \
                source/skyboxwidget.cpp \
                source/tooltabwidget.cpp \
    source/generatorwidget.cpp \
    source/param/intvaluelink.cpp \
    source/param/paramlink.cpp \
    source/event/heightmapevent.cpp \
    source/event/modelevent.cpp

HEADERS  +=	include/mainwindow.hpp \
                include/openglwindow.hpp \
                include/tooltabwidget.hpp \
                include/modelwidget.hpp \
                include/particlewidget.hpp \
                include/skyboxwidget.hpp \
    include/generatorwidget.hpp \
    include/param/intvaluelink.hpp \
    include/param/paramlink.hpp \
    include/event/heightmapevent.hpp \
    include/event/modelevent.hpp

FORMS    += 	interface/mainwindow.ui \
                interface/particlewidget.ui \
                interface/modelwidget.ui \
                interface/skyboxwidget.ui \
                interface/tooltabwidget.ui \
    interface/generatorwidget.ui

RESOURCES +=    ress.qrc

#TODO : find a way to disable shadow build
#DESTDIR
MOC_DIR =       mov
UI_DIR =        ui
RCC_DIR =       rcc
OBJECTS_DIR =   obj

CONFIG +=       c++14

unix: LIBS +=           -L/usr/local/lib/ -lEngine
unix: INCLUDEPATH +=    -I/usr/local/include/


win32: LIBS += -LC:/Libraries/Binaries/Release/x64/ -lEngine
win32: INCLUDEPATH += -I C:/Libraries/Includes
