#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T17:26:47
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CCEditor
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    oglwidget.cpp \
    torus.cpp \
    oglmatinit.cpp \
    elipsoid.cpp

HEADERS  += window.h \
    oglwidget.h \
    torus.h \
    edge.h \
    elipsoid.h

FORMS    += window.ui
