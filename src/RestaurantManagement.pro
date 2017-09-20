#-------------------------------------------------
#
# Project created by QtCreator 2017-09-15T14:03:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RestaurantManagement
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
        mainwindow.cpp \
    registerwindow.cpp \
    abstractshow.cpp \
    user.cpp \
    customer.cpp \
    customermainwindow.cpp \
    customermainwindow.cpp \
    dish.cpp \
    admin.cpp \
    adminmainwindow.cpp \
    cookmainwindow.cpp \
    cook.cpp \
    waiter.cpp \
    waitermainwindow.cpp \
    manager.cpp \
    managermainwindow.cpp

HEADERS += \
        mainwindow.h \
    registerwindow.h \
    abstractshow.h \
    user.h \
    customer.h \
    customermainwindow.h \
    customermainwindow.h \
    dish.h \
    admin.h \
    adminmainwindow.h \
    cookmainwindow.h \
    cook.h \
    waiter.h \
    waitermainwindow.h \
    manager.h \
    managermainwindow.h

FORMS += \
        mainwindow.ui \
    registerwindow.ui \
    customermainwindow.ui \
    customercacu.ui \
    customerprogress.ui \
    adminmainwindow.ui \
    adminuserctrl.ui \
    cookmainwindow.ui \
    waitermainwindow.ui \
    managermainwindow.ui
