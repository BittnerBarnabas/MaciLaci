TEMPLATE = app
TARGET = MaciLaci
QT += core widgets gui
CONFIG += release
CONFIG += c++14
OUTDIR = $$OUT_PWD/bin
DEFINES += QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += objects
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./Implementation/ImplUtility.h \
    ./Implementation/ImpTypes.h \
    ./Implementation/ImplGame.h \
    ./View/ViewGridLabel.h \
    ./View/GameView.h
SOURCES += ./main.cpp \
    ./Implementation/ImplGame.cpp \
    ./Implementation/ImplUtility.cpp \
    ./Implementation/ImpTypes.cpp \
    ./View/GameView.cpp \
    ./View/ViewGridLabel.cpp
FORMS += ./eva_bead_2.ui
RESOURCES += eva_bead_2.qrc
maps.path = $$OUT_PWD/Maps
maps.files = ./Maps/*
target.path = $$OUT_PWD
INSTALLS += maps
INSTALLS += target
CONFIG(nocpp14) {
    DEFINES += nocpp14
}