#-------------------------------------------------
#
# Project created by QtCreator 2017-03-19T09:33:24
#
#-------------------------------------------------

QT       += core gui multimedia multimedia-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:RC_ICONS += icon.ico
CONFIG += static
TARGET = ltnc2017
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    mainwindow.cpp \
    play/Cell.cpp \
    play/Row.cpp \
    play/BottomBar.cpp \
    play/Music.cpp \
    play/PlayScreen.cpp \
    playwindow.cpp \
	play/Score.cpp \
	play/Lives.cpp \
    scorescreen.cpp
SOURCES +=
SOURCES +=

HEADERS  += \
    mainwindow.h \
    play/Cell.h \
    play/Row.h \
    play/const.h \
    play/BottomBar.h \
    play/Music.h \
    play/PlayScreen.h \
    play/Mouse.h \
    Game.h \
    play/Score.h \
    play/Lives.h \
    playwindow.h \
    scorescreen.h
HEADERS  +=

FORMS    += \
    mainwindow.ui \
    scorescreen.ui

DISTFILES += \
    notes/1.wav \
    notes/10.wav \
    notes/11.wav \
    notes/12.wav \
    notes/13.wav \
    notes/14.wav \
    notes/15.wav \
    notes/16.wav \
    notes/17.wav \
    notes/18.wav \
    notes/19.wav \
    notes/2.wav \
    notes/20.wav \
    notes/21.wav \
    notes/22.wav \
    notes/23.wav \
    notes/24.wav \
    notes/25.wav \
    notes/26.wav \
    notes/27.wav \
    notes/28.wav \
    notes/29.wav \
    notes/3.wav \
    notes/30.wav \
    notes/31.wav \
    notes/32.wav \
    notes/33.wav \
    notes/34.wav \
    notes/35.wav \
    notes/36.wav \
    notes/37.wav \
    notes/38.wav \
    notes/39.wav \
    notes/4.wav \
    notes/40.wav \
    notes/41.wav \
    notes/42.wav \
    notes/43.wav \
    notes/44.wav \
    notes/45.wav \
    notes/46.wav \
    notes/47.wav \
    notes/48.wav \
    notes/49.wav \
    notes/5.wav \
    notes/50.wav \
    notes/51.wav \
    notes/52.wav \
    notes/53.wav \
    notes/54.wav \
    notes/55.wav \
    notes/56.wav \
    notes/57.wav \
    notes/58.wav \
    notes/59.wav \
    notes/6.wav \
    notes/60.wav \
    notes/61.wav \
    notes/62.wav \
    notes/63.wav \
    notes/64.wav \
    notes/65.wav \
    notes/66.wav \
    notes/67.wav \
    notes/68.wav \
    notes/7.wav \
    notes/8.wav \
    notes/9.wav

RESOURCES += \
    notes.qrc \
    images.qrc
