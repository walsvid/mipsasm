#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T20:44:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mipsasmcore
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    assembler.cpp \
    highlighter.cpp

HEADERS  += mainwindow.h \
    assembler.h \
    highlighter.h

RESOURCES = application.qrc
