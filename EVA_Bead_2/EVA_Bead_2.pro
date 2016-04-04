TEMPLATE = app
TARGET = MaciLaci
DESTDIR = ./bin
QT += core widgets gui
CONFIG += release
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
QMAKE_CXXFLAGS += -std=c++14
