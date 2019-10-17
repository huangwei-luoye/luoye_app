#ifndef CUDPCOMMUNICATION_H
#define CUDPCOMMUNICATION_H

#include <QWidget>
#include <ControlSercice/RecvCollectDataThread.h>
#include <UtilityClasses/CWaitObjectManager.h>


const static quint16 TryCount = 2;

namespace Ui {
class CUdpCommunication;
}

class CUdpCommunication : public QWidget
{
    Q_OBJECT

public:
    explicit CUdpCommunication(QWidget *parent = nullptr);
    ~CUdpCommunication();
    CWaitObjectManager m_waitMgr;

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_clearAll_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();
    bool CheckIsConnect();

private:
    Ui::CUdpCommunication *ui;
    bool isConnect;
    RecvCollectDataThread m_RecvCollectThread;

    bool processAckProtocol(const QByteArray &data);
    void SendCmdToTdsBoard(quint8 cmd);
    Q_SIGNAL void StartRecvSignal();
    Q_SIGNAL void StopRecvSignal();
    Q_SIGNAL void InitThreadSignal();
    Q_SIGNAL void ClosePaintSignal();
    Q_SIGNAL void StartRecvCollectDataSignal();
    Q_SLOT void OnDealRecvUdpData(const QByteArray &recvData);
    Q_SLOT void OnUpdateProgress(quint32 maxPkg, quint32 currentIndex);
    Q_SLOT void OnCollectDataFinish(bool isSuccess);


};

#endif // CUDPCOMMUNICATION_H
