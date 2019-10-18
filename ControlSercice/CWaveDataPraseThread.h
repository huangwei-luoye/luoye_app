#ifndef CWAVEDATAPRASETHREAD_H
#define CWAVEDATAPRASETHREAD_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QList>
#include <QPointF>

class CWaveDataPraseThread : public QObject
{
    Q_OBJECT
public:
    explicit CWaveDataPraseThread(QObject *parent = nullptr);
    ~CWaveDataPraseThread();



signals:

public slots:

private:

    qint32 m_maxSize;
    qint32 m_index;
    QTimer *m_pTimer;
    QThread m_workThread;
    QList<QPointF> m_listPoint;
    QByteArray m_arraySrcData;
    QList<QPointF> m_sendPoint;

    Q_SIGNAL void ShowWaveSignal(const QList<QPointF> &series);
    Q_SLOT void OnSourceWave(const QByteArray &data,bool isEnd);
    Q_SLOT void OnProcessData();
    Q_SLOT void OnCloseTimer();

};

#endif // CWAVEDATAPRASETHREAD_H
