#-------------------------------------------------
#
# Project created by QtCreator 2019-12-14T18:40:27
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dictClient
TEMPLATE = app


SOURCES += main.cpp\
        logindialog.cpp \
    dictdialog.cpp

HEADERS  += logindialog.h \
    dictdialog.h

FORMS    += logindialog.ui \
    dictdialog.ui
