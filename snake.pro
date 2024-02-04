TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    snake.cpp

HEADERS += \
    snake.h
FORMS += \
    main.ui

LIBS += /usr/lib/x86_64-linux-gnu/libncursesw.so

