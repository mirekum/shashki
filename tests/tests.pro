TEMPLATE = app
TARGET = ../test
DEPENDPATH += . ../src
INCLUDEPATH += . ../src
QT += testlib network
CONFIG += qt debug warn_off qtestlib
OBJECTS_DIR = ../bin/tests
MOC_DIR = ../bin/tests
DEFINES += DATADIR=\\\"$$DATADIR\\\"

HEADERS += test_board.h \
           experiment.h \
           Players/ai.h \
           Model/board.h

SOURCES += main.cpp \
           test_board.cpp \
           experiment.cpp \
           Players/ai.cpp \
           Model/board.cpp

