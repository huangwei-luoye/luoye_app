#ifndef NETWORK_H
#define NETWORK_H

#include <winsock2.h>
#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include "Libuv/uv.h"

class RAII
{
    std::function<void(void)> onDel;
public:
    RAII(std::function<void(void)> onDelete) : onDel(onDelete) {}
    ~RAII() { onDel(); }
};

// 数据发送事件
struct SendData
{
    QString ip;
    quint16 port;
    QByteArray data;
};

// socket对象的标识符，通过 地址-端口 双元组标识
using SocketAddr = QPair<QString, quint16>;

// 获取错误码对应的描述字符串
inline QString uvError(int errorCode)
{
    QString ret = QStringLiteral("%1 : %2");
    ret = ret.arg(uv_err_name(errorCode));
    ret = ret.arg(uv_strerror(errorCode));
    return ret;
}

// 用于分配接收缓冲的回调函数
inline void alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
    Q_UNUSED(handle)
    buf->base = static_cast<char*>(malloc(suggested_size));
    buf->len = suggested_size;
}

// 用于刷新本地地址列表
inline void refreshLocalAddress(QComboBox* box)
{
    box->clear();
    int index = 0;
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    QNetworkInterface inaddr_any_interface;
    for (const QNetworkInterface& ifce : interfaces)
    {
        bool find_inaddr_any = false;
        QList<QNetworkAddressEntry> entries = ifce.addressEntries();
        for (const QNetworkAddressEntry& entry : entries)
        {
            if (entry.ip().protocol() != QAbstractSocket::IPv4Protocol) continue;
            QString ip = entry.ip().toString();
            if (ip.startsWith(QStringLiteral("169.254"))) continue;
            if (ip == "127.0.0.1")
            {
                find_inaddr_any = true;
                inaddr_any_interface = ifce;
                break;
            }
        }
        if (find_inaddr_any) break;
    }
    box->addItem("127.0.0.1");
    box->setItemData(index, inaddr_any_interface.hardwareAddress(), Qt::UserRole);
    box->setItemData(index, inaddr_any_interface.humanReadableName(), Qt::UserRole + 1);

    for (const QNetworkInterface& ifce : interfaces)
    {
        QList<QNetworkAddressEntry> entries = ifce.addressEntries();
        for (const QNetworkAddressEntry& entry : entries)
        {
            if (entry.ip().protocol() != QAbstractSocket::IPv4Protocol) continue;
            QString ip = entry.ip().toString();
            if (ip.startsWith(QStringLiteral("169.254"))) continue;
            if (ip == "127.0.0.1") continue;
            box->addItem(ip);
            box->setItemData(index, ifce.hardwareAddress(), Qt::UserRole);
            box->setItemData(index, ifce.humanReadableName(), Qt::UserRole + 1);
            ++index;
        }
    }
}

template<typename Socket>
inline int initializeSocketOption(Socket* socket)
{
    uv_os_fd_t fd;
    int err = uv_fileno(reinterpret_cast<uv_handle_t*>(socket), &fd);
    if (err != 0) {
        return err;
    }
    uv_os_sock_t s = uv_os_sock_t(fd);

    int reuseaddr = 1;
    setsockopt(s,
               SOL_SOCKET ,
               SO_REUSEADDR,
               reinterpret_cast<const char*>(&reuseaddr),
               sizeof(reuseaddr));

    linger l;
    l.l_onoff = 1;
    l.l_linger = 0;
    setsockopt(s,
               SOL_SOCKET,
               SO_LINGER,
               reinterpret_cast<const char*>(&l),
               sizeof(l));

    return 0;
}

#endif // NETWORK_H
