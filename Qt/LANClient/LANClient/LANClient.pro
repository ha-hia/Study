#-------------------------------------------------
#
# Project created by QtCreator 2021-07-04T22:07:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LANClient
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
        View\CustomLabel.cpp \
        View\loginwidget.cpp \
        Control\IMTcpSocket.cpp \
    View\IMRegisterUi.cpp \
    Control/IMRegisterCtrl.cpp

HEADERS += \
        View\CustomLabel.h \
        View\loginwidget.h \
        Control\IMTcpSocket.h \
    View\IMRegisterUi.h \
    Control/IMConstant.h \
    Control/IMRegisterCtrl.h

RESOURCES += \
    image.qrc

FORMS += \
    View\IMRegisterUi.ui
