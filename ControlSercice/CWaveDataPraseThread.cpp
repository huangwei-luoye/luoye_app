#include "CWaveDataPraseThread.h"
#include "UtilityClasses/CTools.h"
#include <QMetaType>
#include <QDebug>
#define LIST_MAXSIZE (1024*1024*5)

CWaveDataPraseThread::CWaveDataPraseThread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QList<QPointF>>("QList<QPointF>");

    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(10);
    m_maxSize = 1000;
    m_index = 0;
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnProcessData()));
    this->moveToThread(&m_workThread);
    m_workThread.start();
}

CWaveDataPraseThread::~CWaveDataPraseThread()
{
    m_workThread.quit();
    m_workThread.wait();
}
/**
 * @brief CWaveDataPraseThread::OnSourceWave解析处理数据
 * @param data
 */
void CWaveDataPraseThread::OnSourceWave(const QByteArray &data, bool isEnd)
{

    if(m_listPoint.size() < LIST_MAXSIZE)
    {
        m_listPoint += CTools::BumaTosrcma(data);
    }
    if(isEnd)
    {
        m_pTimer->start();
    }
}

void CWaveDataPraseThread::OnProcessData()
{
    if(m_index >= m_listPoint.count())
    {
        OnCloseTimer();
        return;
    }
    m_sendPoint.append(m_listPoint.at(m_index++));

    if(m_sendPoint.size() >= m_maxSize)
    {
        m_sendPoint.removeFirst();
    }
    QList<QPointF> _data;
    for(int loop = 0; loop < m_sendPoint.count(); loop++)
    {
        _data.append(QPointF(loop,m_sendPoint.at(loop).y()));
    }
    emit ShowWaveSignal(_data);
}

void CWaveDataPraseThread::OnCloseTimer()
{
    m_pTimer->stop();
    m_listPoint.clear();
    m_index = 0;
}
