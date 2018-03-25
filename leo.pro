#-------------------------------------------------
#
# Project created by QtCreator 2018-03-17T14:14:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = leo
TEMPLATE = app
LIBS+=-L. -lsqlite3

SOURCES += main.cpp\
    crossword/table.cpp \
    crossword.cpp \
    mainwindows.cpp \
    const.cpp \
    settings.cpp \
    eng_rus.cpp

HEADERS  += \
    crossword/table.h \
    const.h \
    word.h \
    bd.h \
    crossword.h \
    mainwindows.h \
    settings.h \
    eng_rus.h
