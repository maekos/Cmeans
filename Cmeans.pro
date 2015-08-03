#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T22:17:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cmeans
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fuzzy_clustering.cpp \
    stats.cpp \
    csvdata.cpp

HEADERS  += mainwindow.h \
    fuzzy_clustering.hpp \
    stats.h \
    csvdata.h

FORMS    += mainwindow.ui
