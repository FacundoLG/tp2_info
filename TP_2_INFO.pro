TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        date.c \
        file.c \
        generators.c \
        log.c \
        main.c \
        patient.c

HEADERS += \
    date.h \
    file.h \
    generators.h \
    log.h \
    patient.h
