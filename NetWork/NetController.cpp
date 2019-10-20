#include "NetController.h"
#include "QDebug"
#include "UtilityClasses/CTools.h"
#include "UtilityClasses/CTools.h"
#include <QDir>
#include <QDateTime>

#define USE_LIBUV

NetController::NetController()
{
    m_pTcpSocket = nullptr;
    m_pUdpSocket = nullptr;
    m_pLibuvSocket = nullptr;
    m_isBindSuccess = false;
    if(!QDir("./log/").exists())
    {
        QDir().mkpath("./log/");
    }

}

NetController::~NetController()
{
    if(m_pUdpSocket)
    {
        delete m_pUdpSocket;
        m_pUdpSocket = nullptr;
    }
    if(m_pLibuvSocket)
    {
        delete m_pLibuvSocket;
        m_pUdpSocket = nullptr;
    }
}

bool NetController::OnOpenUdpNetwork(const QString &localIp, quint16 localPort)
{
#ifdef USE_LIBUV

    m_pLibuvSocket = new Udp(this);
    m_pLibuvSocket->bind(localIp, localPort);
    m_pLibuvSocket->startRecv();

    connect(m_pLibuvSocket,SIGNAL(bindSuccessed()),this, SLOT(OnBindSuccessed()));
    connect(m_pLibuvSocket, SIGNAL(recvData(QByteArray)),this, SLOT(OnRecvData(QByteArray)));
    CTools::Delay(100);
#else
    m_pUdpSocket = new QUdpSocket(this);
    QHostAddress hostAddr;
    hostAddr.setAddress(localIp);
    bool ret = m_pUdpSocket->bind(hostAddr,localPort,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);


    connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(OnProcessUdpReadData()));
    connect(m_pUdpSocket, SIGNAL(disconnected()), m_pUdpSocket, SLOT(deleteLater()));
#endif

//    if(m_logFile.isOpen())
//    {
//        m_logFile.close();
//    }

//    QString fileName("./log/"+QDateTime::currentDateTime().toString("yyyy_MM_dd.hh_mm_ss") + ".dat");
//    m_logFile.setFileName(fileName);
//    m_logFile.open(QIODevice::WriteOnly | QIODevice::Text);

    return m_isBindSuccess;

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

        emit UdpProcessReciveDataSignal(udpData);

        //qDebug()<<CTools::ByteArrayToString(udpData)<<"\n";
//        QString log = CTools::ByteArrayToString(udpData);
//        if(!log.isEmpty())
//        {
//            if(m_logFile.isOpen())
//            {
//                m_logFile.write(QString(log+"\n").toStdString().c_str());
//                m_logFile.flush();
//            }
//        }

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

#ifdef USE_LIBUV

    m_pLibuvSocket->sendTo(ip,port,data);

#else
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
#endif
}

void NetController::OnBindSuccessed()
{
    //qDebug()<<"bind successed\n";
    m_isBindSuccess = true;
}

void NetController::OnRecvData(const QByteArray &data)
{
      emit UdpProcessReciveDataSignal(data);

//    QString log = CTools::ByteArrayToString(data);
//    if(!log.isEmpty())
//    {
//        if(m_logFile.isOpen())
//        {
//            m_logFile.write(QString(log+"\n").toStdString().c_str());
//            m_logFile.flush();
//        }
//    }
}
