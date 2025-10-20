QT += core gui network widgets

CONFIG += c++11

TARGET = ElBuenGusto
TEMPLATE = app

SOURCES += \
    main.cpp \
    cocina.cpp \
    mainwindow.cpp \
    tarjeta_especialidades.cpp

HEADERS += \
    cocina.h \
    mainwindow.h \
    tarjeta_especialidades.h

FORMS += \
    cocina.ui \
    mainwindow.ui \
    tarjeta_especialidades.ui

RESOURCES += \
    img.qrc