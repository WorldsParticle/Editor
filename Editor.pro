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

#unix: LIBS += -L/usr/local/lib/ -lEngine
#unix: I    NCLUDEPATH += -I/usr/local/include/

LIBS += -L$$OUT_PWD/../Engine/cmake/ -lEngine
INCLUDEPATH += $$PWD/../Engine/include/

CONFIG += warn_off
  QMAKE_CXXFLAGS_WARN_OFF =
   QMAKE_CFLAGS_WARN_OFF =
QMAKE_CXXFLAGS += -fPIC -Wctor-dtor-privacy -Wnoexcept -Wnon-virtual-dtor -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wno-pmf-conversions -Wsign-promo -Wdouble-promotion -Wmissing-include-dirs -Wswitch-default -Wfloat-equal -Wzero-as-null-pointer-constant -Wuseless-cast -Wconversion -Wlogical-op -Wmissing-declarations -Winline -Wshadow -Wall -Wextra



RESOURCES += \
    ress.qrc

