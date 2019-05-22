#-------------------------------------------------
#
# Project created by QtCreator 2019-02-22T13:16:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AdvancedGraphics
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    collapsewidget.cpp \
    scene.cpp \
    gameobject.cpp \
    component.cpp \
    hierarchy.cpp \
    inspector.cpp \
    transform.cpp \
    transformwidget.cpp \
    appmanager.cpp \
    openglwidget.cpp \
    hierarchyobject.cpp


HEADERS += \
        mainwindow.h \
    collapsewidget.h \
    scene.h \
    gameobject.h \
    component.h \
    hierarchy.h \
    inspector.h \
    transform.h \
    transformwidget.h \
    appmanager.h \
    openglwidget.h \
    hierarchyobject.h

FORMS += \
        mainwindow.ui \
    collapsewidget.ui \
    hierarchy.ui \
    inspector.ui \
    transformwidget.ui \
    aboutgl.ui \
    hierarchyobject.ui

RESOURCES += \
    resources.qrc
CONFIG += console
