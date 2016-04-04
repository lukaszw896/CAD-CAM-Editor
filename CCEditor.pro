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
    drawable/torus.cpp \
    RenderWidget/oglwidget.cpp \
    Camera/camera.cpp \
    drawable/drawable.cpp \
    drawable/point.cpp \
    uiaccess.cpp \
    transclass.cpp \
    drawerwindow.cpp

HEADERS  += window.h \
    edge.h \
    drawable/torus.h \
    RenderWidget/oglwidget.h \
    Camera/camera.h \
    drawable/drawable.h \
    drawable/point.h \
    uiaccess.h \
    transclass.h \
    drawerwindow.h

FORMS    += window.ui
