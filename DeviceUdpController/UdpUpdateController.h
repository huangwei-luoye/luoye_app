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
//    QByteArray m_srcPoint;
    quint16 m_currentPkgIndex;

    Q_SLOT void OnProcessRecvData(const QByteArray &udpData);
    Q_SIGNAL void RecvCollectDataSignal(const QByteArray &data, bool isEnd, int loss);
    Q_SIGNAL void UpdateProgressSignal(quint32 maxSize, quint32 currentSize);
};

#endif // UDPUPDATECONTROLLER_H
