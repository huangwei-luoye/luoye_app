#include "Udp.h"
#include "UdpPrivate.h"
#include "UvUdpSocket.h"
#include "UdpManager.h"
#include "Network.h"

Udp::Udp(QObject* parent)
    : QObject(parent),
      d_ptr(new UdpPrivate(this))
{
}

Udp::~Udp()
{
    delete d_ptr;
}

void Udp::bind(const QString& addr, quint16 port)
{
    Q_D(Udp);
    // 若配置未发生改变，则忽略本次请求
    if (d->socket)
    {
        if ((d->socket->localAddr() == addr)
            && (d->socket->localPort() == port))
        {
            emit bindSuccessed();
            return;
        }
    }
    // 获取对应socket
    d->socket.clear();
    d->socket = UdpManager::instance().findSocket(addr, port);
    // 初始化信号槽连接
    d->connectSocket();
}

void Udp::configSend(const QString& addr, quint16 port)
{
    Q_D(Udp);
    d->destAddr = addr;
    d->destPort = port;
}

void Udp::send(const QByteArray& data)
{
    Q_D(Udp);
    if (!d->socket) {
        return;
    }
    emit sendTo(d->destAddr, d->destPort, data);
}

QList<QPair<QString, quint16>> Udp::filter() const
{
    Q_D(const Udp);
    return d->filters;
}

void Udp::setFilter(QList<QPair<QString, quint16>> filters)
{
    Q_D(Udp);
    d->filters = filters;
}

QString Udp::localAddr() const
{
    Q_D(const Udp);
    if (d->socket) {
        return d->socket->localAddr();
    }
    return {};
}

void Udp::setLocalAddr(const QString& addr)
{
    bind(addr, localPort());
}

quint16 Udp::localPort() const
{
    Q_D(const Udp);
    if (d->socket) {
        return d->socket->localPort();
    }
    return {};
}

void Udp::setLocalPort(quint16 port)
{
    bind(localAddr(), port);
}

QString Udp::destAddr() const
{
    Q_D(const Udp);
    return d->destAddr;
}

void Udp::setDestAddr(const QString& addr)
{
    if (addr != destAddr()) {
        configSend(addr, destPort());
    }
}

quint16 Udp::destPort() const
{
    Q_D(const Udp);
    return d->destPort;
}

void Udp::setDestPort(quint16 port)
{
    if (port != destPort()) {
        configSend(destAddr(), port);
    }
}

QStringList Udp::multicastGroups() const
{
    Q_D(const Udp);
    if (d->socket) {
        return d->socket->multicastGroups();
    }
    return {};
}

UdpPrivate::UdpPrivate(Udp* parent)
    : QObject(parent),
      q_ptr(parent)
{
}

void UdpPrivate::connectSocket()
{
    Q_Q(Udp);

    UvUdpSocket* s = socket.data();

    disconnect(this, nullptr, s, nullptr);
    disconnect(s, nullptr, this, nullptr);

    connect(s, &UvUdpSocket::bindSuccessed,
            q, [q]{
       emit q->bindSuccessed();
    }, Qt::QueuedConnection);

    connect(s, &UvUdpSocket::sendFinished,
            q, [q](const QString& addr, quint16 port, const QByteArray& data){
       emit q->sendFinished(addr, port, data);
    }, Qt::QueuedConnection);

    connect(s, &UvUdpSocket::sendFailed,
            q, [q](const QString& addr, quint16 port, const QString& errorString, const QByteArray& data){
       emit q->sendFailed(addr, port, errorString, data);
    }, Qt::QueuedConnection);

    connect(s, &UvUdpSocket::recvData,
            q, [this, q](const QByteArray& data, const QString& addr, quint16 port){
        // 若设置了接收过滤，则查询过滤信息
        if (!filters.isEmpty())
        {
            if (!filters.contains(qMakePair(addr, port)))
                return;
        }
       emit q->recvFrom(addr, port, data);
       emit q->recvData(data);
    }, Qt::QueuedConnection);

    connect(s, &UvUdpSocket::recvError,
            q, [q](const QString& errorString){
       emit q->recvError(errorString);
    }, Qt::QueuedConnection);

    connect(s, &UvUdpSocket::error,
            q, [q](const QString& errorString, int errorCode){
        emit q->error(errorString, errorCode);
    }, Qt::QueuedConnection);

    connect(q, &Udp::startRecv,
            s, &UvUdpSocket::startRecv,
            Qt::QueuedConnection);

    connect(q, &Udp::stopRecv,
            s, &UvUdpSocket::stopRecv,
            Qt::QueuedConnection);

    connect(q, &Udp::joinMulticastGroup,
            s, &UvUdpSocket::joinMulticastGroup,
            Qt::QueuedConnection);

    connect(q, &Udp::leaveMulticastGroup,
            s, &UvUdpSocket::leaveMulticastGroup,
            Qt::QueuedConnection);

    connect(q, &Udp::sendTo,
            s, &UvUdpSocket::send,
            Qt::QueuedConnection);
}
