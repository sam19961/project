# -------------------------------------------------
# Project created by QtCreator 2009-01-10T14:03:23
# -------------------------------------------------
QT += network widgets
TARGET = MyQServer
TEMPLATE = app

SOURCES += ./main1.cpp \
    ./MySocketServer.cpp \
    ./MySocketClient.cpp \
    ./dialog.cpp

HEADERS += ./MySocketServer.h \
    ./MySocketClient.h \
    ./dialog.h

CONFIG += c++11
