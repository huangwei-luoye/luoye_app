#include "UvUdpSocket.h"
#include "Libuv/QEventDispatcherLibuv.h"

UvUdpSocket::UvUdpSocket(const QString& hostAddress, quint16 localPort)
    : socket(new uv_udp_t)
{
    uv_ip4_addr(hostAddress.toUtf8().constData(), localPort, &localAddress);
    socket->data = this;
}

UvUdpSocket::~UvUdpSocket()
{
    uv_close(reinterpret_cast<uv_handle_t*>(socket),
             &UvUdpSocket::onClosed);
}

void UvUdpSocket::init()
{
    // 获取本线程事件循环，初始化socket
    QEventDispatcherLibuv* dispatcher = qobject_cast<QEventDispatcherLibuv*>(QAbstractEventDispatcher::instance());
    uv_loop_t* loop = static_cast<uv_loop_t*>(dispatcher->currentLoop());
    int err = uv_udp_init(loop, socket);
    if (err != 0)
    {
        emit error(uvError(err), err);
        return;
    }

    // 将socket bind到本地地址
    err = uv_udp_bind(socket, reinterpret_cast<const struct sockaddr*>(&localAddress), UV_UDP_REUSEADDR);
    if (err != 0)
    {
        emit error(uvError(err), err);
        return;
    }
    emit bindSuccessed();
}

void UvUdpSocket::refreshLocalAddr()
{
    int len = sizeof(localAddress);
    uv_udp_getsockname(socket,
                       reinterpret_cast<sockaddr*>(&localAddress),
                       &len);
}

void UvUdpSocket::startRecv()
{
    int err = uv_udp_recv_start(socket,
                                &alloc,
                                &UvUdpSocket::onRecv);
    if (err != 0) {
        emit error(uvError(err), err);
    }
}

void UvUdpSocket::stopRecv()
{
    uv_udp_recv_stop(socket);
}

void UvUdpSocket::send(const QString& addr, quint16 port, const QByteArray& data)
{
    // 初始化目的地址
    struct sockaddr_in send_addr;
    uv_ip4_addr(addr.toUtf8().constData(),
                port,
                &send_addr);

    // 初始化数据包
    sendQueue.enqueue({addr, port, data}); // 将数据包加入待处理队列
    const QByteArray& sendData = sendQueue[sendQueue.count() - 1].data;
    uv_buf_t msg = uv_buf_init(const_cast<char*>(sendData.constData()), uint(sendData.length()));

    // 发送数据包
    uv_udp_send_t sendReq;
    int err = uv_udp_send(&sendReq,
                          socket,
                          &msg,
                          1,
                          reinterpret_cast<const struct sockaddr*>(&send_addr),
                          &UvUdpSocket::onSendFinished);
    if (err != 0)
    {
        QString errorString = uvError(err);
        emit sendFailed(addr, port, errorString, data);
        emit error(errorString, err);
    }
}

void UvUdpSocket::joinMulticastGroup(const QString& hostAddress)
{
    if (!multicast.contains(hostAddress))
    {
        int err = uv_udp_set_membership(socket,
                                        hostAddress.toUtf8().constData(),
                                        localAddr().toUtf8().constData(),
                                        UV_JOIN_GROUP);
        if (err != 0) {
            emit error(uvError(err), err);
        } else {
            multicast << hostAddress;
        }
    }
}

void UvUdpSocket::leaveMulticastGroup(const QString& hostAddress)
{
    if (multicast.contains(hostAddress))
    {
        int err = uv_udp_set_membership(socket,
                                        hostAddress.toUtf8().constData(),
                                        localAddr().toUtf8().constData(),
                                        UV_LEAVE_GROUP);
        if (err != 0) {
            emit error(uvError(err), err);
        } else {
            multicast.removeAll(hostAddress);
        }
    }
}

QString UvUdpSocket::localAddr() const
{
    const_cast<UvUdpSocket*>(this)->refreshLocalAddr();
    char addr[17] = { 0 };
    uv_ip4_name(&localAddress, addr, 16);
    return QString::fromUtf8(addr);
}

quint16 UvUdpSocket::localPort() const
{
    const_cast<UvUdpSocket*>(this)->refreshLocalAddr();
    return ntohs(localAddress.sin_port);
}

QStringList UvUdpSocket::multicastGroups() const
{
    return multicast;
}

void UvUdpSocket::onSendFinished(uv_udp_send_t* req, int status)
{
    Q_UNUSED(req)
    Q_UNUSED(status)

    UvUdpSocket* socket = static_cast<UvUdpSocket*>(req->handle->data); // 获取本事件对应的socket
    SendData data = socket->sendQueue.dequeue(); // 获取本事件对应的数据

    if (!status) { // 发送成功
        emit socket->sendFinished(data.ip, data.port, data.data);
    } else { // 发送失败
        emit socket->sendFailed(data.ip, data.port, uvError(status), data.data);
    }
}

void UvUdpSocket::onRecv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const sockaddr* addr, unsigned flags)
{
    Q_UNUSED(flags)

    // 退出时自动释放缓冲区
    RAII guard( [buf]{ free(buf->base); } );

    // 获取本事件对应的socket
    UvUdpSocket* socket = static_cast<UvUdpSocket*>(handle->data);

    // 接收失败
    if (nread < 0)
    {
        emit socket->recvError(uvError(nread));
        return;
    }
    if (nread == 0) return;

    // 解析发送方地址，发送信号
    char sender[17] = { 0 };
    const sockaddr_in* addr_in = reinterpret_cast<const sockaddr_in*>(addr);
    uv_ip4_name(addr_in, sender, 16);
    QString sendAddr = sender;
    quint16 sendPort = ntohs(addr_in->sin_port);
    QByteArray data(buf->base, nread);
    emit socket->recvData(data, sendAddr, sendPort);
}

void UvUdpSocket::onClosed(uv_handle_t* handle)
{
    uv_udp_t* socket = reinterpret_cast<uv_udp_t*>(handle);
    delete socket;
}
