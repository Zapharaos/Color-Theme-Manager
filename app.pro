QT       += core gui xml
QT		+=	network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


OBJECTS_DIR = ./.obj
UI_DIR      = ./ui
MOC_DIR		= ./.obj
TS_DIR		= ./ts
SRC_DIR		= ./src
SRC_WIDGETS_DIR = $${SRC_DIR}/Widgets
INCLUDE_DIR = ./include
INCLUDE_WIDGETS_DIR = $${INCLUDE_DIR}/Widgets
INCLUDEPATH += $${INCLUDE_DIR} $${INCLUDE_WIDGETS_DIR}
VPATH += $${SRC_DIR} $${SRC_WIDGETS_DIR} $${INCLUDE_DIR} $${INCLUDE_WIDGETS_DIR} $${UI_DIR}

SOURCES += \
	mainwindow.cpp \
	main.cpp \
	Widgets/orientablepushbutton.cpp \
	Theme.cpp \
	Themes.cpp \
	Widgets/menuitemwidget.cpp \
	Widgets/themewidget.cpp \
	Widgets/colorwidget.cpp \
	XMLReader.cpp \
	colorpair.cpp

HEADERS += \
    Theme.h \
    Themes.h \
    Widgets/orientablepushbutton.h \
    Widgets/menuitemwidget.h \
    Widgets/themewidget.h \
    Widgets/colorwidget.h \
    XMLReader.h \
    colorpair.h \
	mainwindow.h

FORMS += \
	mainwindow.ui \
	colorwidget.ui \
	menuitemwidget.ui \
	themewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
