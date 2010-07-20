# base settings
TEMPLATE = app
QT+= network
TARGET = sr
DEPENDPATH += .
INCLUDEPATH += .
QT += testlib
CONFIG += qt debug warn_off qtestlib
DEFINES += DATADIR=\\\"$$DATADIR\\\"

HEADERS += board.h \
           player.h \
           network_player.h \
           
SOURCES += board.cpp \
           network_player.cpp \
           mainsr.cpp

unix {
	# variables
	isEmpty(PREFIX) {
		PREFIX = /usr
    }
	BINDIR = $$PREFIX/bin
	DATADIR =$$PREFIX/share
	DEFINES += DATADIR=\"$$DATADIR\" PKGDATADIR=\"$$PKGDATADIR\"
	
	# installation
	INSTALLS += target desktop iconxpm icon26 icon40 icon64
	target.path =$$BINDIR
	desktop.path = $$DATADIR/applications/hildon
	desktop.files += ../data/$${TARGET}.desktop
	iconxpm.path = $$DATADIR/pixmap
	iconxpm.files += ../data/maemo/$${TARGET}.xpm
	icon26.path = $$DATADIR/icons/hicolor/26x26/apps
	icon26.files += ../data/26x26/$${TARGET}.png
	icon40.path = $$DATADIR/icons/hicolor/40x40/apps
	icon40.files += ../data/40x40/$${TARGET}.png
	icon64.path = $$DATADIR/icons/hicolor/64x64/apps
	icon64.files += ../data/64x64/$${TARGET}.png
}

