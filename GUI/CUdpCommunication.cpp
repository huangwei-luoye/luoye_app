#include "CUdpCommunication.h"
#include "ui_CUdpCommunication.h"
#include "./ControlSercice/DeviceController.h"
#include "./UtilityClasses/CQssFileAdaption.h"
#include "./GUI/QcharWiget.h"
#include "./UtilityClasses/CSetting.h"
#include "./LogOpreate/LogOperate.h"
#include "./UtilityClasses/CTools.h"
#include "NetWork/UdpProtocol.h"
#include "UtilityClasses/CSetting.h"
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>


CUdpCommunication::CUdpCommunication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CUdpCommunication)
{
    ui->setupUi(this);
    isConnect = false;

    QVBoxLayout *pVBoxLayout = new QVBoxLayout(ui->widget_wave);
    QcharWiget *pCharWiget = new QcharWiget();
    pVBoxLayout->addWidget(pCharWiget);
    pVBoxLayout->setMargin(0);
    ui->widget_wave->setLayout(pVBoxLayout);


    connect(this, SIGNAL(InitThreadSignal()), &m_RecvCollectThread, SLOT(OnInitThread()),Qt::QueuedConnection);
    connect(this, SIGNAL(StartRecvSignal()), &m_RecvCollectThread, SLOT(OnStartRecv()));
    connect(this, SIGNAL(StopRecvSignal()), &m_RecvCollectThread, SLOT(OnStopRecv()));
    connect(&m_RecvCollectThread, SIGNAL(WaveDataSignal(QByteArray, bool)), pCharWiget, SLOT(OnWaveData(QByteArray,bool)));
    connect(&m_RecvCollectThread,SIGNAL(CollectDataFinishSignal(bool)), this, SLOT(OnCollectDataFinish(bool)));
    connect(&m_RecvCollectThread, SIGNAL(updateProgressSignal(quint32, quint32)), this, SLOT(OnUpdateProgress(quint32, quint32)));
    connect(this,SIGNAL(ClosePaintSignal()), pCharWiget, SLOT(OnClosePaint()));

    QFile styleSheet(CQssFileAdaption::getInstance()->getCommunication());
    if(styleSheet.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(styleSheet.readAll());
    }
}

CUdpCommunication::~CUdpCommunication()
{
    delete ui;
}

void CUdpCommunication::on_pushButton_connect_clicked()
{

     DeviceController *pDeviceContrl = DeviceController::getInstance();
     QString remoteIp = CSetting::getInstance()->getTdsBoardIp();
     quint16 remotePort = CSetting::getInstance()->getTdsBoardPort();
     QByteArray cmdArray;
     MsgCmdUdpAck cmdAck;
     MsgCmdUdp sendCmd;
     bool bRet = false;
     int nTry = 0;

     sendCmd.cmd = CMD_RESET;
     cmdArray.append((const char *)&sendCmd, sizeof(MsgCmdUdp));

    if(ui->pushButton_connect->text() == "连接")
    {
        LogOperate::getinstance()->LogOperaterUi(tr("网络连接中...."),LOG_INFO);
        connect(pDeviceContrl, SIGNAL(ProcessTdsUdpDataSignal(QByteArray)), this, SLOT(OnDealRecvUdpData(QByteArray)));
        do
        {
            m_waitMgr.push(CMD_RESET, 5000);
            pDeviceContrl->SendUdpDataToTds(cmdArray, remoteIp, remotePort);
            bRet = m_waitMgr.waitAll();
            if(bRet)
            {
                break;
            }
        }while((++nTry)<TryCount);
        disconnect(pDeviceContrl, SIGNAL(ProcessTdsUdpDataSignal(QByteArray)), this, SLOT(OnDealRecvUdpData(QByteArray)));
        if(bRet)
        {
            LogOperate::getinstance()->LogOperaterUi(tr("连接成功"),LOG_INFO);
            ui->pushButton_connect->setText("断开");
            isConnect = true;
        }
        else
        {
            LogOperate::getinstance()->LogOperaterUi(tr("连接超时失败，请重试"),LOG_ERROR);
            isConnect = false;
        }
    }
    else
    {
        //DeviceController::getInstance()->CloseTdsBordUdp();
        LogOperate::getinstance()->LogOperaterUi("已断开");
        isConnect = false;
        ui->pushButton_connect->setText("连接");
    }
}

void CUdpCommunication::OnDealRecvUdpData(const QByteArray &recvData)
{
    QString str = CTools::ByteArrayToString(recvData);
    ui->textEdit_udpData->insertPlainText(str);
    if(processAckProtocol(recvData))
    {
        m_waitMgr.wakeOne(CMD_RESET);
    }
}

void CUdpCommunication::OnUpdateProgress(quint32 maxPkg, quint32 currentIndex)
{
    //qDebug()<<"recv signal";
    //qDebug()<<maxPkg<<currentIndex;
    ui->progressBar->setValue((float)currentIndex/(float)maxPkg*100);
}

void CUdpCommunication::OnCollectDataFinish(bool isSuccess)
{
    if(isSuccess)
    {
        ui->progressBar->setValue(100);
    }
    ui->pushButton_start->setEnabled(true);
}

void CUdpCommunication::on_pushButton_clearAll_clicked()
{
    ui->textEdit_udpData->clear();
}

void CUdpCommunication::on_pushButton_send_clicked()
{
    QString str = ui->textEdit_udpData->toPlainText();
    QByteArray sendArray = QByteArray::fromHex(str.toLatin1().data());
    if(!isConnect)
    {
        QMessageBox::warning(this, tr("警告"),tr("请打开连接!"));
        return;
    }
    DeviceController::getInstance()->SendUdpDataToTds(sendArray, CSetting::getInstance()->getTdsBoardIp(),CSetting::getInstance()->getTdsBoardPort());

}


bool CUdpCommunication::processAckProtocol(const QByteArray &data)
{
     if(data.size() >= (int)sizeof(MsgCmdUdp))
     {
         MsgCmdUdp protocol;
         memcpy(&protocol, data.data(),sizeof(MsgCmdUdp));

         if(protocol.head == ProtocolHead && protocol.end == ProtocolEnd)
         {
             if(protocol.cmd == CMD_RESET)
             {
                 return true;
             }
         }
     }

     return false;
}

void CUdpCommunication::SendCmdToTdsBoard(quint8 cmd)
{
    DeviceController *pDeviceCtr = DeviceController::getInstance();
    QString remoteIp = CSetting::getInstance()->getTdsBoardIp();
    quint16 remotePort = CSetting::getInstance()->getTdsBoardPort();

    QByteArray sendcmd;
    MsgCmdUdp  msgCmd;

    msgCmd.cmd = cmd;
    sendcmd.append((const char*)&msgCmd, sizeof(MsgCmdUdp));

    pDeviceCtr->SendUdpDataToTds(sendcmd, remoteIp, remotePort);

}


void CUdpCommunication::on_pushButton_start_clicked()
{

    if(CheckIsConnect())
    {
        ui->pushButton_start->setEnabled(false);
        ui->progressBar->setValue(0);
        SendCmdToTdsBoard(CMD_START);
        emit ClosePaintSignal();
        emit InitThreadSignal();
        emit StartRecvSignal();
    }
    else {
        QMessageBox::warning(this, tr("警告"),tr("请打开连接!"));
    }
}

void CUdpCommunication::on_pushButton_stop_clicked()
{
    ui->pushButton_stop->setEnabled(false);
    emit StopRecvSignal();
    ui->pushButton_stop->setEnabled(true);
}

bool CUdpCommunication::CheckIsConnect()
{
    return isConnect;
}
