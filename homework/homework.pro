#-------------------------------------------------
#
# Project created by QtCreator 2024-05-26T16:24:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = homework
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    form.cpp \
    form1.cpp \
    form2.cpp \
    form3.cpp

HEADERS += \
        widget.h \
    form.h \
    form1.h \
    form2.h \
    form3.h

FORMS += \
        widget.ui \
    form.ui \
    form1.ui \
    form2.ui \
    form3.ui

RESOURCES += \
    img.qrc
