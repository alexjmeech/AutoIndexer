TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    String.cpp \
    AutoIndexer.cpp \
    test.cpp

HEADERS += \
    IndexOutOfBoundsException.h \
    ConcurrentModificationException.h \
    ArrayListIterator.h \
    ArrayList.h \
    ArrayWrapper.h \
    String.h \
    AutoIndexer.h \
    catch.hpp
