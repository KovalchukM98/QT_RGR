#-------------------------------------------------
#
# Project created by QtCreator 2021-11-21T16:31:59
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RGR
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
    add_form.cpp \
    day_form.cpp \
    search_form.cpp \
    faq_form.cpp

HEADERS += \
        mainwindow.h \
    add_form.h \
    day_form.h \
    search_form.h \
    faq_form.h

FORMS += \
        mainwindow.ui \
    add_form.ui \
    day_form.ui \
    search_form.ui \
    faq_form.ui
