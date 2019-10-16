#include "CSetting.h"
#include <QFile>
#include <QDomDocument>
#include <QDomNode>

CSetting::CSetting()
{
}

CSetting::~CSetting()
{
}

CSetting *CSetting::getInstance()
{
    static CSetting instance;
    return &instance;
}

bool CSetting::init(const QString &xmlFile)
{
    QFile mFile(xmlFile);

    if(!mFile.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&mFile))
    {
        mFile.close();
        return false;
    }
    mFile.close();

    QDomElement root = doc.documentElement();

    QDomNode tcpConfig = root.namedItem("Tcp-config");
    if(!tcpConfig.isNull())
    {
        QDomNode localNode = tcpConfig.namedItem("本地");
        if(!localNode.isNull())
        {
            m_LocalIp = localNode.toElement().attribute("ip");
            m_LocalPort = localNode.toElement().attribute("port").toUInt();
        }
    }

    QDomNode udpConfig = root.namedItem("Udp-config");
    if(!udpConfig.isNull())
    {
        QDomNode tdsNode = udpConfig.namedItem("TDS板");
        if(!tdsNode.isNull())
        {
           m_TdsBoardUdpIp = tdsNode.toElement().attribute("ip");
           m_TdsBoardUdpPort = tdsNode.toElement().attribute("port").toUInt();
        }
    }

    return true;
}

QString CSetting::getLocalIp()
{
    return m_LocalIp;
}

quint16 CSetting::getLocalPort()
{
    return m_LocalPort;
}

QString CSetting::getTdsBoardIp()
{
    return m_TdsBoardUdpIp;
}

quint16 CSetting::getTdsBoardPort()
{
    return m_TdsBoardUdpPort;
}
