#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T09:52:50
#
#-------------------------------------------------

QT += core
QT += gui
QT += network
QT += widgets
QT += printsupport

TARGET = PowerBall
TEMPLATE = app

CONFIG += c++11

SOURCES += \
	main.cpp \
	LottoWindow.cpp \
	PowerballReader.cpp \
	PowerBallTracker.cpp \
	QuickPickDialog.cpp

HEADERS  += \
	LottoWindow.h \
	Draw.h \
	PowerballReader.h \
	PowerBallTracker.h \
	QuickPickDialog.h

FORMS    += \
	LottoWindow.ui \
	QuickPickDialog.ui

DISTFILES += \
	README.md \
	.gitignore \
	LICENSE
