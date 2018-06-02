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
	PowerballReader.cpp \
	PowerBallTracker.cpp \
	QuickPickDialog.cpp \
    PreferencesDialog.cpp \
    LottoWidget.cpp

HEADERS  += \
	Draw.h \
	PowerballReader.h \
	PowerBallTracker.h \
	QuickPickDialog.h \
    PreferencesDialog.h \
    LottoWidget.h

FORMS    += \
	QuickPickDialog.ui \
    PreferencesDialog.ui \
    LottoWidget.ui

DISTFILES += \
	README.md \
	.gitignore \
	LICENSE
