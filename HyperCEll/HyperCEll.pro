#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T20:02:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HyperCEll
TEMPLATE = app


SOURCES += main.cpp\
        controller.cpp \
    cell.cpp \
    customscene.cpp \
    view.cpp \
    collider.cpp \
    borderguard.cpp \
    settler.cpp \
    utility.cpp \
    ia.cpp

HEADERS  += controller.h \
    cell.h \
    customscene.h \
    view.h \
    collider.h \
    borderguard.h \
    settler.h \
    utility.h \
    ia.h \
    config.h

FORMS    +=

RESOURCES += \
    ressources.qrc
