#include "DeviceController.h"

DeviceController::DeviceController(QObject *parent) :
    QObject(parent)
{
    connect(&m_TdsBoardUdpCtr, SIGNAL(UdpProcessReciveDataSignal(QByteArray)), this, SIGNAL(ProcessTdsUdpDataSignal(QByteArray)));
    connect(this, SIGNAL(SendUdpDataSingal(QByteArray,QString,quint16)), &m_TdsBoardUdpCtr, SLOT(OnSendUdpData(QByteArray,QString,quint16)));
}

DeviceController::~DeviceController()
{

}

DeviceController *DeviceController::getInstance()
{
    static DeviceController instance;
    return &instance;
}

bool DeviceController::OpenTdsBoardUdp(const QString &ip, quint16 port)
{
    return m_TdsBoardUdpCtr.OnOpenUdpNetwork(ip, port);
}

void DeviceController::SendUdpDataToTds(const QByteArray &data, const QString &ip, quint16 port)
{
    emit SendUdpDataSingal(data, ip, port);
}

void DeviceController::CloseTdsBordUdp()
{
    m_TdsBoardUdpCtr.OnCloseUdpNetWorke();
}
