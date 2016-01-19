#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T19:13:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelPoiEditor
TEMPLATE = app
CONFIG += C++11

SOURCES += \
	main.cpp \
	widget.cpp \

HEADERS  += \
	widget.h \
	Mode.hpp \
	Count.hpp \
	Image.hpp \
		

FORMS    += widget.ui
