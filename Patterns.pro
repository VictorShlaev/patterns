TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    adapter.hpp \
    bridge.hpp \
    builder.hpp \
    composite.hpp \
    factory.hpp \
    factoryMethod.hpp \
    prototype.hpp \
    singleton.hpp \
    wrapper.hpp
