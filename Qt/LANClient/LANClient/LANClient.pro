#-------------------------------------------------
#
# Project created by QtCreator 2021-07-04T22:07:57
#
#-------------------------------------------------

QT       += core gui network sql

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
    Control/IMRegisterCtrl.cpp \
    Control/IMLoginCtrl.cpp \
    View/IMMainWidget.cpp \
    Control/IMDatabaseCtrl.cpp \
    Control/IMMainCtrl.cpp \
    Control/IMUser.cpp \
    View/IMLatestMessageListWidget.cpp \
    View/IMToolBox.cpp \
    View/IMChatWidget.cpp \
    View/IMFriendButton.cpp \
    View/IMInformationWidget.cpp \
    View/IMLinkButton.cpp \
    View/IMMessageManageWidget.cpp \
    View/IMLinkFriendButton.cpp \
    View/IMSearchListWidget.cpp \
    Control/IMClientFileCtrl.cpp \
    View/IMFileReceiverWidget.cpp \
    View/IMFileSenderWidget.cpp \
    View/IMFriendListWidget.cpp \
    View/IMInputTextEdit.cpp \
    View/IMLocalMessageWidget.cpp \
    View/IMNetWorkMessageWidget.cpp \
    View/IMMessageWidget.cpp \
    View/CustomCalendar.cpp \
    View/CustomLineEdit.cpp \
    View/CalendarDialog.cpp \
    View/CustomComboBox.cpp

HEADERS += \
        View\CustomLabel.h \
        View\loginwidget.h \
        Control\IMTcpSocket.h \
    View\IMRegisterUi.h \
    Control/IMConstant.h \
    Control/IMRegisterCtrl.h \
    Control/IMLoginCtrl.h \
    View/IMMainWidget.h \
    Control/IMDatabaseCtrl.h \
    Control/IMMainCtrl.h \
    Control/IMUser.h \
    View/IMLatestMessageListWidget.h \
    View/IMToolBox.h \
    View/IMChatWidget.h \
    View/IMFriendButton.h \
    View/IMInformationWidget.h \
    View/IMLinkButton.h \
    View/IMMessageManageWidget.h \
    View/IMLinkFriendButton.h \
    View/IMSearchListWidget.h \
    Control/IMClientFileCtrl.h \
    View/IMFileReceiverWidget.h \
    View/IMFileSenderWidget.h \
    View/IMFriendListWidget.h \
    View/IMInputTextEdit.h \
    View/IMLocalMessageWidget.h \
    View/IMNetWorkMessageWidget.h \
    View/IMMessageWidget.h \
    View/CustomCalendar.h \
    View/CustomLineEdit.h \
    View/CalendarDialog.h \
    View/CustomComboBox.h

RESOURCES += \
    image.qrc

FORMS += \
    View\IMRegisterUi.ui

