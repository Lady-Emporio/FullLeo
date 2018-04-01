#-------------------------------------------------
#
# Project created by QtCreator 2018-03-31T12:34:23
#
#-------------------------------------------------

QT       += core gui widgets multimedia multimediawidgets

TARGET = FullLeo
TEMPLATE = app
LIBS+=-L. -lsqlite3

SOURCES += main.cpp\
        mainwindow.cpp \
    backend/leo_const.cpp \
    backend/leo_setting.cpp \
    act/crossword/crossword.cpp \
    act/crossword/table.cpp \
    act/engrus/eng_rus.cpp

HEADERS  += mainwindow.h \
    backend/leo_const.h \
    backend/leo_setting.h \
    backend/word.h \
    sqlite3.h \
    act/crossword/crossword.h \
    act/crossword/table.h \
    act/engrus/eng_rus.h
