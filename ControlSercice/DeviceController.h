#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include "NetWork/NetController.h"

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = 0);
    virtual ~DeviceController();

    static DeviceController* getInstance();

    bool OpenTdsBoardUdp(const QString &ip, quint16 port);
    void SendUdpDataToTds(const QByteArray &data, const QString &ip, quint16 port);
    void CloseTdsBordUdp();

private:
    NetController m_TdsBoardUdpCtr;

    Q_SIGNAL void ProcessTdsUdpDataSignal(const QByteArray &data);
    Q_SIGNAL void SendUdpDataSingal(const QByteArray &data, const QString &ip, quint16 port);

};

#endif // DEVICECONTROLLER_H
