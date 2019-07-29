QT += core
QT -= gui

CONFIG += c++11

TARGET = SnakeConsole
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cobrinha.cpp \
    corpo.cpp \
    singleton.cpp

HEADERS += \
    cobrinha.h \
    corpo.h \
    singleton.h \
    state.h \
    memento.h
