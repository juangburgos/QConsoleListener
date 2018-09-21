QT     += core
CONFIG += c++11

TARGET  = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include($$PWD/../src/qconsolelistener.pri)

SOURCES += main.cpp

