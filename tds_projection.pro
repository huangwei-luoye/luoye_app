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
    ControlSercice/CWaveDataPraseThread.cpp \
    NetWork/Udp/Libuv/QEventDispatcherLibuv_p.cpp \
    NetWork/Udp/Libuv/QEventDispatcherLibuvGui.cpp \
    NetWork/Udp/Libuv/socknot_p.cpp \
    NetWork/Udp/Libuv/timers_p.cpp \
    NetWork/Udp/Libuv/win32_utils.cpp \
    NetWork/Udp/Udp.cpp \
    NetWork/Udp/UdpManager.cpp \
    NetWork/Udp/UvUdpSocket.cpp

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
    ControlSercice/CWaveDataPraseThread.h \
    NetWork/Udp/Libuv/android-ifaddrs.h \
    NetWork/Udp/Libuv/pthread-barrier.h \
    NetWork/Udp/Libuv/QEventDispatcherLibuv.h \
    NetWork/Udp/Libuv/QEventDispatcherLibuv_p.h \
    NetWork/Udp/Libuv/QEventDispatcherLibuvGui.h \
    NetWork/Udp/Libuv/qt4compat.h \
    NetWork/Udp/Libuv/stdint-msvc2008.h \
    NetWork/Udp/Libuv/tree.h \
    NetWork/Udp/Libuv/uv-aix.h \
    NetWork/Udp/Libuv/uv-bsd.h \
    NetWork/Udp/Libuv/uv-darwin.h \
    NetWork/Udp/Libuv/uv-errno.h \
    NetWork/Udp/Libuv/uv-linux.h \
    NetWork/Udp/Libuv/uv-os390.h \
    NetWork/Udp/Libuv/uv-posix.h \
    NetWork/Udp/Libuv/uv-sunos.h \
    NetWork/Udp/Libuv/uv-threadpool.h \
    NetWork/Udp/Libuv/uv-unix.h \
    NetWork/Udp/Libuv/uv-version.h \
    NetWork/Udp/Libuv/uv-win.h \
    NetWork/Udp/Libuv/uv.h \
    NetWork/Udp/Libuv/win32_utils.h \
    NetWork/Udp/Network.h \
    NetWork/Udp/Udp.h \
    NetWork/Udp/Udp_global.h \
    NetWork/Udp/UdpManager.h \
    NetWork/Udp/UdpPrivate.h \
    NetWork/Udp/UvUdpSocket.h

FORMS    += mainwindow.ui \
    LogOpreate/LogOperateWidget.ui \
    GUI/CUdpCommunication.ui \
    GUI/QcharWiget.ui

win32: LIBS += -lws2_32 -lpsapi -luser32 -liphlpapi -luserenv



win32: LIBS += -L$$PWD/bin/lib/ -llibuv

INCLUDEPATH += $$PWD/bin
DEPENDPATH += $$PWD/bin
