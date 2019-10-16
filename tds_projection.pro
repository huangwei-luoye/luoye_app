#-------------------------------------------------
#
# Project created by QtCreator 2019-09-25T11:40:56
#
#-------------------------------------------------

QT       += core gui network xml
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tds_projection
TEMPLATE = app

DESTDIR = $$PWD/bin
CONFIG +=c++11
RC_FILE = app.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    UtilityClasses/CQssFileAdaption.cpp \
    LogOpreate/LogOperate.cpp \
    LogOpreate/LogOperateTableMode.cpp \
    LogOpreate/LogOperateWidget.cpp \
    GUI/CUdpCommunication.cpp \
    UtilityClasses/CSetting.cpp \
    NetWork/NetController.cpp \
    ControlSercice/DeviceController.cpp \
    UtilityClasses/CTools.cpp \
    ControlSercice/ExperimentFileOperat.cpp \
    DeviceUdpController/UdpUpdateController.cpp \
    ControlSercice/RecvCollectDataThread.cpp \
    GUI/QcharWiget.cpp \
    UtilityClasses/CWaitObject.cpp \
    UtilityClasses/CWaitObjectManager.cpp \
    ControlSercice/CWaveDataPraseThread.cpp

HEADERS  += mainwindow.h \
    UtilityClasses/CQssFileAdaption.h \
    LogOpreate/LogOperate.h \
    LogOpreate/LogOperateTableMode.h \
    LogOpreate/LogOperateWidget.h \
    GUI/CUdpCommunication.h \
    UtilityClasses/CSetting.h \
    Global.h \
    GlobalProtocol.h \
    NetWork/NetController.h \
    ControlSercice/DeviceController.h \
    UtilityClasses/CTools.h \
    NetWork/UdpProtocol.h \
    ControlSercice/ExperimentFileOperat.h \
    DeviceUdpController/UdpUpdateController.h \
    ControlSercice/RecvCollectDataThread.h \
    GUI/QcharWiget.h \
    UtilityClasses/CWaitObject.h \
    UtilityClasses/CWaitObjectManager.h \
    ControlSercice/CWaveDataPraseThread.h

FORMS    += mainwindow.ui \
    LogOpreate/LogOperateWidget.ui \
    GUI/CUdpCommunication.ui \
    GUI/QcharWiget.ui

RESOURCES +=
