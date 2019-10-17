#ifndef UDP_H
#define UDP_H

#include <QtCore>
#include "Udp_global.h"

// TODO broadcast
// Udp接口类
class UdpPrivate;
class Udp : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Udp)
    UdpPrivate* d_ptr;

    using Filter_t = QList<QPair<QString, quint16> >;

public:
    explicit Udp(QObject* parent = nullptr);
    virtual ~Udp() override;

    // 发生错误，参数为错误信息
    Q_SIGNAL void error(const QString& reason, int errorCode);

    // 绑定本地地址，参数为地址和端口
    Q_SLOT void bind(const QString& addr, quint16 port);
    // 端口绑定成功
    Q_SIGNAL void bindSuccessed();

    // 启动监听
    Q_SIGNAL void startRecv();
    // 停止监听
    Q_SIGNAL void stopRecv();

    // 从客户端接收到新数据，参数为客户端地址、端口、数据内容
    Q_SIGNAL void recvFrom(const QString& addr, quint16 port, const QByteArray& data);
    // 接收到新数据，参数为数据内容
    Q_SIGNAL void recvData(const QByteArray& data);
    // 发生接收错误，参数为错误信息
    Q_SIGNAL void recvError(const QString& reason);

    // 加入组播，参数为组播地址
    Q_SIGNAL void joinMulticastGroup(const QString& addr);
    // 退出组播，参数为组播地址
    Q_SIGNAL void leaveMulticastGroup(const QString& addr);
    // 获取已加入的组播列表
    Q_SLOT QStringList multicastGroups() const;

    // 设置发送参数，参数为目标地址和端口
    Q_SLOT void configSend(const QString& addr, quint16 port);
    // 发送数据至已配置的目标地址，参数为数据内容
    Q_SLOT void send(const QByteArray& data);
    // 发送数据，参数为目标地址、端口、数据内容
    Q_SIGNAL void sendTo(const QString addr, quint16 port, const QByteArray& data);
    // 数据发送成功，参数为目标ip端口、已发送的数据
    Q_SIGNAL void sendFinished(const QString& addr, quint16 port, const QByteArray& data);
    // 数据发送失败，参数为目标ip端口、失败原因、已发送的数据
    Q_SIGNAL void sendFailed(const QString& addr, quint16 port, const QString& reason, const QByteArray& data);

    // 获取接收过滤器
    Q_SLOT QList<QPair<QString, quint16>> filter() const;
    // 设置接收过滤，参数为运行通过的地址-端口对列表
    Q_SLOT void setFilter(QList<QPair<QString, quint16>> filters);

    // 获取本地地址
    Q_SLOT QString localAddr() const;
    // 设置本地地址
    Q_SLOT void setLocalAddr(const QString& addr);
    // 获取本地端口
    Q_SLOT quint16 localPort() const;
    // 设置本地端口
    Q_SLOT void setLocalPort(quint16 port);

    // 获取远端地址
    Q_SLOT QString destAddr() const;
    // 设置远端地址
    Q_SLOT void setDestAddr(const QString& addr);
    // 获取远端端口
    Q_SLOT quint16 destPort() const;
    // 设置远端端口
    Q_SLOT void setDestPort(quint16 port);
};

#endif // UDP_H
