#-------------------------------------------------
#
# Project created by QtCreator 2013-06-17T10:39:38
#
#-------------------------------------------------

QT       += core gui
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku
TEMPLATE = app


SOURCES += main.cpp\
        sudokumain.cpp \
    mysqlconnector.cpp

HEADERS  += sudokumain.h \
    mysqlconnector.h

FORMS    += sudokumain.ui
