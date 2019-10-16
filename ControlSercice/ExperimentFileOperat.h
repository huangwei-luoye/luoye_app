#ifndef EXPERIMENTFILEOPERAT_H
#define EXPERIMENTFILEOPERAT_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QMap>

class ExperimentFileOperat : public QObject
{
    Q_OBJECT
public:
    explicit ExperimentFileOperat(QObject *parent = 0);
    virtual  ~ExperimentFileOperat();

    void SetFileName(const QMap<quint8, QString> &fileName);

private:

    QThread m_WorkThread;
    QMap <quint8, QFile*> m_FileMap;
    QMap <quint8, QString > m_FileNameMap;

    Q_SLOT void OnOperatResultData(quint8 channel, const QByteArray &data, bool isEnd);
    Q_SIGNAL void OperatFinishSignal(quint8 channel);
};

#endif // EXPERIMENTFILEOPERAT_H
