#-------------------------------------------------
#
# Project created by QtCreator 2012-07-04T00:22:04
#
#-------------------------------------------------

QT       += core gui

TARGET = AlgAc[tc]
TEMPLATE = app

# Comentar la siguiente línea si no se compila en Windows
RC_FILE += iconapp.qrc

SOURCES += main.cpp\
    gui/*.cpp \
    gram/*.cpp

HEADERS  += gui/*.h \
    gram/*.h

FORMS    += \
    gui/*.ui

RESOURCES += \
    resources.qrc \

#Comentar la siguiente sección si no se usan librerias estáticas
QMAKE_CXXFLAGS += -fpermissive # Flag usado para esquivar advertencias con g++
CONFIG += static
static {
    CONFIG += static
    QTPLUGIN += qico # Comentar si no se compila en Windows
    DEFINES += STATIC
    message("Static build.")
}
