#ifndef UDPMANAGER_H
#define UDPMANAGER_H

#include "Network.h"

class UvUdpSocket;

// 用于管理所有UdpSocket对象
class UdpManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(UdpManager)
public:
    static UdpManager& instance(); // 单例模式

    // 查询指定地址端口的对应socket，若无则新建一个
    QSharedPointer<UvUdpSocket> findSocket(const QString& addr, quint16 port);

private:
    UdpManager();
    ~UdpManager();

    // 将socket对象移动至子线程并进行初始化
    void initSocket(QSharedPointer<UvUdpSocket>& socket);

    // 所有socket对象列表
    QHash<SocketAddr, QWeakPointer<UvUdpSocket>> sockets;

    QMutex mutex;
    QThread* uvThread;
};

#endif // UDPMANAGER_H
