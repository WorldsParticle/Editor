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

LIBS += -L$$OUT_PWD/../Engine/build/release/ -lEngine
LIBS += -L/usr/local/lib -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath #only nux
LIBS += -lGLU # pour test bullet sans use l'engine
INCLUDEPATH += $$PWD/../Engine/include/
INCLUDEPATH += /usr/local/include/bullet/ #only nux


RESOURCES += \
    ress.qrc


