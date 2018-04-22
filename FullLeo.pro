#-------------------------------------------------
#
# Project created by QtCreator 2018-03-31T12:34:23
#
#-------------------------------------------------

QT       += core gui widgets multimedia multimediawidgets sql

TARGET = FullLeo
TEMPLATE = app
LIBS+=-L. -lsqlite3

SOURCES += main.cpp\
        mainwindow.cpp \
    backend/leo_const.cpp \
    backend/leo_setting.cpp \
    act/crossword/crossword.cpp \
    act/crossword/table.cpp \
    act/engrus/eng_rus.cpp \
    backend/list_word_db.cpp \
    act/write/input_write.cpp \
    act/notvisual/not_visual_one_row.cpp \
    backend/error_count.cpp \
    act/engrus/x_y.cpp \
    act/sprint/sprint_choose.cpp

HEADERS  += mainwindow.h \
    backend/leo_const.h \
    backend/leo_setting.h \
    backend/word.h \
    sqlite3.h \
    act/crossword/crossword.h \
    act/crossword/table.h \
    backend/list_word_db.h \
    act/write/input_write.h \
    act/notvisual/not_visual_one_row.h \
    backend/error_count.h \
    act/engrus/eng_rus.h \
    act/engrus/x_y.h \
    act/sprint/sprint_choose.h

DISTFILES +=
