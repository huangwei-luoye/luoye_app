#include "NetController.h"
#include "QDebug"
#include "UtilityClasses/CTools.h"
NetController::NetController()
{
    m_pTcpSocket = nullptr;
    m_pUdpSocket = nullptr;

}

NetController::~NetController()
{
    if(m_pUdpSocket)
    {
        delete m_pUdpSocket;
        m_pUdpSocket = nullptr;
    }
}

bool NetController::OnOpenUdpNetwork(const QString &localIp, quint16 localPort)
{
    m_pUdpSocket = new QUdpSocket(this);
    QHostAddress hostAddr;
    hostAddr.setAddress(localIp);
    bool ret = m_pUdpSocket->bind(hostAddr,localPort,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(OnProcessUdpReadData()));
    connect(m_pUdpSocket, SIGNAL(disconnected()), m_pUdpSocket, SLOT(deleteLater()));

    return ret;

}

void NetController::OnCloseUdpNetWorke()
{
    if(m_pUdpSocket)
    {
        delete m_pUdpSocket;
        m_pUdpSocket = nullptr;
    }
}

void NetController::OnProcessUdpReadData()
{
    while(m_pUdpSocket->hasPendingDatagrams())
    {
        QByteArray udpData;
        QHostAddress host;
        quint16 port = 0;

        udpData.resize(m_pUdpSocket->pendingDatagramSize());
        m_pUdpSocket->readDatagram(udpData.data(),udpData.size(), &host, &port);

        //qDebug()<<"1111111 "<<QString(CTools::ByteArrayToString(udpData));
        emit UdpProcessReciveDataSignal(udpData);
    }

}
/**
 * @brief NetController::OnSendUdpData 发送udp数据
 * @param data udp数据
 * @param ip 远程ip地址
 * @param port 远程端口
 */
void NetController::OnSendUdpData(const QByteArray &data, const QString ip, quint16 port)
{
    //1. 发送数据
    int sendSize = m_pUdpSocket->writeDatagram(data, data.length(), QHostAddress(ip), port);

    //2.判断是否发送成功
    if(data.length() != sendSize)
    {
        switch(sendSize)
        {
        case QAbstractSocket::UnknownSocketError:
            // "未知错误，请尝试重启程序";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            // "服务端已关闭";
            break;
        case QAbstractSocket::SocketTimeoutError:
            // "UDP报文发送超时！";
            break;
        case QAbstractSocket::AddressInUseError:
            // "端口号：已经被占用，请修改端口号！"
            break;
        case QAbstractSocket::NetworkError:
            // "网络故障，可能网线松了"
            break;
        default:
            break;
        }
        emit NetWorkErrSignal(ErrWrite);
    }

}
