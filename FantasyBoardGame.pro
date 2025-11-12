TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Armour.cpp \
        Board.cpp \
        BoardSquare.cpp \
        Character.cpp \
        Enemy.cpp \
        Item.cpp \
        Player.cpp \
        Ring.cpp \
        Shield.cpp \
        Utility.cpp \
        Weapon.cpp \
        main.cpp

HEADERS += \
    Armour.h \
    Board.h \
    BoardSquare.h \
    Character.h \
    Constants.h \
    Enemy.h \
    Item.h \
    Player.h \
    Ring.h \
    Shield.h \
    Utility.h \
    Weapon.h
