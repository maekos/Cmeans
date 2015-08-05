#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T22:17:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cmeans
TEMPLATE = app

INCLUDEPATH+= ./ \
              ./control/include/ \
              ./vista/include

SOURCES += main.cpp \
        ./control/src/fuzzy_clustering.cpp \
        ./control/src/stats.cpp \
        ./control/src/csvdata.cpp \
        ./vista/src/mainwindow.cpp \
        ./vista/src/estadisticasvista.cpp \
        ./vista/src/algoritmovista.cpp

HEADERS  +=  ./vista/include/mainwindow.h \
            ./control/include/fuzzy_clustering.hpp \
            ./control/include/stats.h \
            ./control/include/csvdata.h \
            ./vista/include/estadisticasvista.h \
            ./vista/include/algoritmovista.h

FORMS    += ./forms/mainwindow.ui \
            ./forms/vistaestadisticas.ui \
            ./forms/algoritmovista.ui
