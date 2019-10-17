#ifndef NETCONTROLLER_H
#define NETCONTROLLER_H
#include <QTcpSocket>
#include <QUdpSocket>
#include <QFile>

enum NetControlErr
{
    ErrConnect,
    ErrDisConnect,
    ErrWrite,
};

class NetController : public QObject
{
    Q_OBJECT

public:
    NetController();
    virtual ~NetController();

    Q_SLOT bool OnOpenUdpNetwork(const QString &ip, quint16 port);
    Q_SLOT void OnCloseUdpNetWorke();


private:
    QFile m_logFile;
    QTcpSocket *m_pTcpSocket;
    QUdpSocket *m_pUdpSocket;

    Q_SLOT void OnProcessUdpReadData();
    Q_SLOT void OnSendUdpData(const QByteArray &data, const QString ip, quint16 port);

    Q_SIGNAL void UdpProcessReciveDataSignal(const QByteArray &Data);
    Q_SIGNAL void testDataSignal(const QByteArray &Data);
    Q_SIGNAL void NetWorkErrSignal(NetControlErr err);
};

#endif // NETCONTROLLER_H
