#include "UdpUpdateController.h"
#include "./ControlSercice/DeviceController.h"
#include "./NetWork/UdpProtocol.h"
#include "./LogOpreate/LogOperate.h"
#include <QtEndian>
#include <QDebug>

#define MAX_POINT (1024*1)

UdpUpdateController::UdpUpdateController(QObject *parent) :
    QObject(parent)
{
    m_currentPkgIndex = 0;
    m_pointMax = MAX_POINT;
}

UdpUpdateController::~UdpUpdateController()
{

}

void UdpUpdateController::RecvUdpData()
{
    m_currentPkgIndex = 0;
    DeviceController *pDeviceCtr = DeviceController::getInstance();
    connect(pDeviceCtr, SIGNAL(ProcessTdsUdpDataSignal(QByteArray)), this, SLOT(OnProcessRecvData(QByteArray)), Qt::DirectConnection);
}
/**
 * @brief UdpUpdateController::OnProcessRecvData//按照协议解析接收到的数据
 * @param udpData
 */
void UdpUpdateController::OnProcessRecvData(const QByteArray &udpData)
{
    MsgUdpDataAckProtocol ProtocolHead;
    quint16 length = udpData.size();

    if(length > (int)sizeof(MsgUdpDataAckProtocol))
    {
        memcpy(&ProtocolHead, udpData.data(), sizeof(ProtocolHead));

        ProtocolHead.head = qFromBigEndian(ProtocolHead.head);
        ProtocolHead.allPoint = qFromBigEndian(ProtocolHead.allPoint);
        ProtocolHead.allFrameCnt = qFromBigEndian(ProtocolHead.allFrameCnt);
        ProtocolHead.currentFramNum = qFromBigEndian(ProtocolHead.currentFramNum);
        ProtocolHead.currentFramDataLen = qFromBigEndian(ProtocolHead.currentFramDataLen);
        bool isEnd = false;

        if(ProtocolHead.head != UdpProtocolAckHead)
        {
            LogOperate::getinstance()->LogOperaterUi(QString("数据头校验错误"),LOG_ERROR);
            return;
        }
        m_currentPkgIndex++;
        if(ProtocolHead.allFrameCnt-1 >= ProtocolHead.currentFramNum)
        {
            m_point += QByteArray(udpData.data()+sizeof(MsgUdpDataAckProtocol),length-sizeof(MsgUdpDataAckProtocol)-sizeof(quint32)-sizeof(quint8));
            emit UpdateProgressSignal(ProtocolHead.allFrameCnt, ProtocolHead.currentFramNum+1);
        }
        if(ProtocolHead.allFrameCnt-1 == ProtocolHead.currentFramNum)
        {
            isEnd = true;
            LogOperate::getinstance()->LogOperaterUi(QString(tr("采集数据接收完成")), LOG_INFO);
        }
        if((quint64)m_point.size() >= m_pointMax || isEnd)
        {

            if((quint64)m_point.size() > m_pointMax)
            {
                //qDebug()<<"5555555";
                //emit RecvCollectDataSignal(m_point, isEnd, ProtocolHead.allFrameCnt-m_currentPkgIndex);
                QByteArray pointData = QByteArray(m_point.data()+m_pointMax, m_point.size()-m_pointMax);
                m_point = pointData;
            }
            else
            {
                emit RecvCollectDataSignal(m_point,isEnd, ProtocolHead.allFrameCnt-m_currentPkgIndex);
                m_point.clear();
                //qDebug()<<"5555555";
            }
            if(isEnd)
            {
                m_point.clear();
                m_currentPkgIndex = 0;

            }
        }
    }
}

