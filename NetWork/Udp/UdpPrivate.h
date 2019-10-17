#ifndef UDPPRIVATE_H
#define UDPPRIVATE_H

#include <QtCore>
#include "UvUdpSocket.h"

// TODO broadcast
// Udp接口类
class Udp;
class UdpPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Udp)
    Udp* q_ptr;

public:
    explicit UdpPrivate(Udp* parent = nullptr);

    void connectSocket();

    QSharedPointer<UvUdpSocket> socket;         // socket对象
    QString destAddr;                           // 目标地址
    quint16 destPort;                           // 目标端口
    QList<QPair<QString, quint16>> filters;     // 接收过滤器
};

#endif // UDPPRIVATE_H
