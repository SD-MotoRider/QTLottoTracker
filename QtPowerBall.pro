#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T09:52:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtLottoTracker
TEMPLATE = app


SOURCES += \
	main.cpp \
	LottoWindow.cpp \
	PowerballReader.cpp \
	PowerBallTracker.cpp

HEADERS  += \
	LottoWindow.h \
	Draw.h \
	PowerballReader.h \
	PowerBallTracker.h

FORMS    += \
	LottoWindow.ui

DISTFILES += \
	README.md \
	.gitignore \
	LICENSE
