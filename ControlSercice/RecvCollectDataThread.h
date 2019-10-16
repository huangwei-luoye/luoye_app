#ifndef RECVCOLLECTDATATHREAD_H
#define RECVCOLLECTDATATHREAD_H
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include "DeviceUdpController/UdpUpdateController.h"
#include "./ExperimentFileOperat.h"
class RecvCollectDataThread : public QObject
{
    Q_OBJECT
public:
    explicit RecvCollectDataThread(QObject *parent = nullptr);
    virtual ~RecvCollectDataThread();

    Q_SLOT void OnInitThread();

signals:

public slots:

private:

    bool m_isRunning;
    bool m_isEnd;
    QTimer *m_pTimer;
    QEventLoop *m_pLoop;

    QThread m_workThread;
    UdpUpdateController *m_pUdpUpdateCtr;
    ExperimentFileOperat *m_pFileOperate;

    Q_SLOT void OnStartRecv();
    Q_SLOT void OnStopRecv();
    Q_SLOT void OnOperatFinish(quint8 channel);
    Q_SLOT void OnRecvCollectData(const QByteArray &data, bool isEnd, int loss);
    Q_SIGNAL void OperatResultDataSignal(quint8 channel, const QByteArray &data, bool isEnd);
    Q_SIGNAL void WaveDataSignal(const QByteArray &data);
    Q_SIGNAL void updateProgressSignal(quint32 maxSize, quint32 currentSize);
    Q_SIGNAL void CollectDataFinishSignal(bool isSuccesse);
    Q_SIGNAL void OpreatCloseFileSignal();
};

#endif // RECVCOLLECTDATATHREAD_H
