#ifndef UDPUPDATECONTROLLER_H
#define UDPUPDATECONTROLLER_H

#include <QObject>

class UdpUpdateController : public QObject
{
    Q_OBJECT
public:
    explicit UdpUpdateController(QObject *parent = nullptr);
    virtual ~UdpUpdateController();

    void RecvUdpData();
signals:

public slots:

private:
    QByteArray m_point;
    quint32 m_pointMax;
//    QByteArray m_srcPoint;
    quint32 m_currentPkgIndex;

    Q_SLOT void OnProcessRecvData(const QByteArray &udpData);
    Q_SIGNAL void RecvCollectDataSignal(const QByteArray &data, bool isEnd, int loss);
    Q_SIGNAL void UpdateProgressSignal(quint32 maxSize, quint32 currentSize);
    Q_SIGNAL void ResetTimerSignal();
};

#endif // UDPUPDATECONTROLLER_H
