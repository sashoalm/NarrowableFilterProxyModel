#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T15:07:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NarrowableFilterProxyModel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    narrowablefilterproxymodel.cpp \
    abstractproxychainmodel.cpp

HEADERS  += mainwindow.h \
    narrowablefilterproxymodel.h \
    abstractproxychainmodel.h

FORMS    += mainwindow.ui
