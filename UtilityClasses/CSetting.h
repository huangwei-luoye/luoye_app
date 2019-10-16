#ifndef CSETTING_H
#define CSETTING_H

#include <QString>

class CSetting
{
public:
    CSetting();
    virtual ~CSetting();

    static CSetting *getInstance();

    bool init(const QString& xmlFile);

    QString getLocalIp();
    quint16 getLocalPort();
    QString getTdsBoardIp();
    quint16 getTdsBoardPort();

private:
    QString m_TdsBoardUdpIp;
    quint16 m_TdsBoardUdpPort;

    QString m_LocalIp;
    quint16 m_LocalPort;
};

#endif // CSETTING_H
