#-------------------------------------------------
#
# Project created by QtCreator 2018-03-17T14:14:44
#
#-------------------------------------------------

QT       += core gui widgets multimedia multimediawidgets

TARGET = leo
TEMPLATE = app
LIBS+=-L. -lsqlite3

SOURCES += main.cpp\
    crossword/table.cpp \
    crossword.cpp \
    mainwindows.cpp \
    const.cpp \
    settings.cpp \
    eng_rus.cpp \
    updown/up_down.cpp \
    updown/rectdown.cpp

HEADERS  += \
    crossword/table.h \
    const.h \
    word.h \
    bd.h \
    crossword.h \
    mainwindows.h \
    settings.h \
    eng_rus.h \
    updown/up_down.h \
    updown/rectdown.h
