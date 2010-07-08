TEMPLATE = app
TARGET = shashki
DEPENDPATH += .
INCLUDEPATH += .
QT += testlib
CONFIG += qt debug warn_off qtestlib

HEADERS += ai.h \
           board.h \
           experiment.h \
           game.h \
           human.h \
           network.h \
           player.h \
           test_board.h

SOURCES += ai.cpp \
           board.cpp \
           experiment.cpp \
           game.cpp \
           human.cpp \
           main.cpp \
           network.cpp \
           test_board.cpp

