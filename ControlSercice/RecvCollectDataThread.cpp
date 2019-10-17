#include "RecvCollectDataThread.h"
#include <QDebug>
#include <LogOpreate/LogOperate.h>
#include "GUI/QcharWiget.h"

RecvCollectDataThread::RecvCollectDataThread(QObject *parent) :
    QObject(parent)
{
    m_pFileOperate = nullptr;
    m_pUdpUpdateCtr = nullptr;

    m_pTimer = new QTimer(this);
    m_pLoop = new QEventLoop(this);

    m_pTimer->setInterval(1000*120);
    m_pTimer->setSingleShot(true);

    connect(m_pTimer, SIGNAL(timeout()), m_pLoop, SLOT(quit()));
    this->moveToThread(&m_workThread);
    m_workThread.start();
}

RecvCollectDataThread::~RecvCollectDataThread()
{
    m_isRunning = false;
    m_workThread.quit();
    m_workThread.wait();
    if(m_pFileOperate)
    {
        delete m_pFileOperate;
        m_pFileOperate = nullptr;
    }
    if(m_pUdpUpdateCtr)
    {
        delete m_pUdpUpdateCtr;
        m_pUdpUpdateCtr = nullptr;
    }
    //qDebug()<<"xigou";
}

void RecvCollectDataThread::OnInitThread()
{
    QcharWiget *pChar = QcharWiget::getInstance();

    if(!m_pFileOperate)
    {
        m_pFileOperate = new ExperimentFileOperat;
    }
    if(!m_pUdpUpdateCtr)
    {
        m_pUdpUpdateCtr = new UdpUpdateController;
        m_pUdpUpdateCtr->RecvUdpData();
    }

    connect(m_pUdpUpdateCtr, SIGNAL(UpdateProgressSignal(quint32, quint32)), this, SIGNAL(updateProgressSignal(quint32, quint32)));
    connect(m_pUdpUpdateCtr, SIGNAL(RecvCollectDataSignal(QByteArray,bool,int)), this, SLOT(OnRecvCollectData(QByteArray, bool, int)));
    connect(m_pUdpUpdateCtr, SIGNAL(ResetTimerSignal()), this, SLOT(OnResetTimer()));
    connect(this, SIGNAL(OperatResultDataSignal(quint8, QByteArray , bool)), m_pFileOperate, SLOT(OnOperatResultData(quint8, QByteArray , bool)));
    connect(this, SIGNAL(WaveDataSignal(QByteArray)), pChar, SLOT(OnWaveData(QByteArray)));
    connect(m_pFileOperate, SIGNAL(OperatFinishSignal(quint8)), this, SLOT(OnOperatFinish(quint8)));
    LogOperate::getinstance()->LogOperaterUi(QString("正在接收回波数据中！"), LOG_INFO);
}

void RecvCollectDataThread::OnStartRecv()
{

    m_isRunning = true;
    m_isEnd = false;
    m_pTimer->start();
    m_pLoop->exec();

    if(m_isRunning)
    {
        if(!m_isEnd)
        {
            LogOperate::getinstance()->LogOperaterUi(QString("波形接收失败，请检查网络设备！"),LOG_ERROR);
            emit CollectDataFinishSignal(false);
        }
    }
    qDebug()<<"22222222";
}

void RecvCollectDataThread::OnStopRecv()
{
    emit OpreatCloseFileSignal();
    if(m_pFileOperate)
    {
        disconnect(this, SIGNAL(OperatResultDataSignal(quint8, QByteArray , bool)), m_pFileOperate, SLOT(OnOperatResultData(quint8, QByteArray , bool)));
    }
    if(m_pUdpUpdateCtr)
    {
        disconnect(m_pUdpUpdateCtr, SIGNAL(UpdateProgressSignal(quint32, quint32)), this, SIGNAL(updateProgressSignal(quint32, quint32)));
        disconnect(m_pUdpUpdateCtr, SIGNAL(RecvCollectDataSignal(QByteArray,bool,int)), this, SLOT(OnRecvCollectData(QByteArray, bool, int)));
    }
    m_isRunning = false;
    m_pLoop->quit();
}

void RecvCollectDataThread::OnResetTimer()
{
    //qDebug()<<"00000000";
    m_pTimer->start();
}

void RecvCollectDataThread::OnOperatFinish(quint8 channel)
{
    m_isEnd = true;
    OnStopRecv();
    emit CollectDataFinishSignal(true);
}

void RecvCollectDataThread::OnRecvCollectData(const QByteArray &data, bool isEnd, int loss)
{
    if(!m_isRunning)
    {
        return;
    }
    emit OperatResultDataSignal(1, data ,isEnd);
    emit WaveDataSignal(data);
    if(isEnd)
    {
        LogOperate::getinstance()->LogOperaterUi(QString("微波采集波形接收100%！"),LOG_INFO);
        if(loss > 0)
        {
            LogOperate::getinstance()->LogOperaterUi(QString("微波脉冲采集回波数据共丢 %1 帧").arg(loss), LOG_ERROR);
        }
        if(loss < 0)
        {
//                        LogOperate::getinstance()->LogOperaterUi(QString("微波脉冲采集通道%1 帧序错误")
//                                                                 .arg(headInfo.publicHead.channel), LOG_WARNING);
        }
    }
    //m_pTimer->start();

}





