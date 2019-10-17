#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "Network.h"
#include "UdpManager.h"

// 封装libuv中udp异步通信接口
class UvUdpSocket : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(UvUdpSocket)
public:
    ~UvUdpSocket();

    // 端口绑定成功
    Q_SIGNAL void bindSuccessed();
    // 数据发送成功
    Q_SIGNAL void sendFinished(const QString& addr, quint16 port, const QByteArray& data);
    // 数据发送失败
    Q_SIGNAL void sendFailed(const QString& addr, quint16 port, const QString& errorString, const QByteArray& data);
    // 收到数据包
    Q_SIGNAL void recvData(const QByteArray& data, const QString& addr, quint16 port);
    // 数据接收错误
    Q_SIGNAL void recvError(const QString& errorString);
    // 运行错误
    Q_SIGNAL void error(const QString& errorString, int errorCode);

    // 启动数据接收监听
    Q_SLOT void startRecv();
    // 停止数据接收监听
    Q_SLOT void stopRecv();
    // 向目标地址发送数据包
    Q_SLOT void send(const QString& addr, quint16 port, const QByteArray& data);
    // 加入组播
    Q_SLOT void joinMulticastGroup(const QString& hostAddress);
    // 退出组播
    Q_SLOT void leaveMulticastGroup(const QString& hostAddress);

    // 绑定的本地地址
    QString localAddr() const;
    // 绑定的本地端口
    quint16 localPort() const;
    // 已加入的组播列表
    QStringList multicastGroups() const;

private:
    friend class UdpManager;
    UvUdpSocket(const QString& hostAddress = QHostAddress(QHostAddress::AnyIPv4).toString(),
                quint16 localPort = 0);

    // 初始化对象，用于跨线程两段构造。会初始化socket对象，并将其bind到本地地址
    Q_SLOT void init();

    void refreshLocalAddr();

    // 用于处理发送结果的回调函数
    static void onSendFinished(uv_udp_send_t* req, int status);
    // 用于处理接收数据的回调函数
    static void onRecv(uv_udp_t* handle,
                       ssize_t nread,
                       const uv_buf_t* buf,
                       const struct sockaddr* addr,
                       unsigned flags);
    // 用于关闭socket时的回调
    static void onClosed(uv_handle_t* handle);

    uv_udp_t* socket;               // socket对象

    sockaddr_in localAddress;       // 本地地址
    QStringList multicast;          // 组播列表

    QQueue<SendData> sendQueue;   // 尚未获得结果的已发送数据列表
};

#endif // UDPSOCKET_H
