CONFIG      += c++11
INCLUDEPATH += $$PWD
HEADERS     += $$PWD/qconsolelistener.h
SOURCES     += $$PWD/qconsolelistener.cpp
win32 {
	include($$PWD/add_qt_path_win.pri)
}