TEMPLATE = app
CONFIG += c++11
SOURCES  = src/qt/main_qt.cpp \
			src/core/Fantome.cpp \
			src/core/Jeu.cpp \
			src/core/Pacman.cpp \
			src/core/Terrain.cpp \
                        src/qt/pacmangraphics.cpp \
    src/qt/fantomegraphicsitem.cpp
HEADERS  = \
			src/core/documentation.h \
			src/core/Fantome.h \
			src/core/Jeu.h \
			src/core/Pacman.h \
			src/core/Terrain.h \
                        src/qt/pacmangraphics.h \
    src/qt/fantomegraphicsitem.h

QT += widgets

INCLUDEPATH += src/core src/qt
