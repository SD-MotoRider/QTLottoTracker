#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T09:52:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtLottoTracker
TEMPLATE = app


SOURCES += \
    main.cpp \
    LottoWindow.cpp \
    LottoTracker.cpp \
    DrawReader.cpp \
    PowerballReader.cpp

HEADERS  += \
    LottoWindow.h \
    LottoTracker.h \
    Draw.h \
    DrawReader.h \
    PowerballReader.h

FORMS    += \
    LottoWindow.ui

DISTFILES += \
    README.md \
    .gitignore \
    LICENSE
