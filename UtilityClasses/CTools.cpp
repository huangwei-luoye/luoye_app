#include "CTools.h"
#include <QEventLoop>
#include <QTimer>
#include <QtEndian>
#include <QDebug>

CTools::CTools()
{
}

QString CTools::ByteArrayToString(const QByteArray &data)
{
    QString str;

    for(qint32 i = 0; i < data.size(); i++)
    {
        char buffer[8] = {0};
        sprintf(buffer, "%02X", (quint8)data.at(i));
        str += buffer;
    }
    return str;
}

void CTools::Delay(quint32 ms)
{
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, SLOT(quit()));

    loop.exec();

}
/**
 * @brief CTools::BumaTosrcma补码转换成源码数据，2个字节为一个数据
 * @param data
 */
QList<QPointF> CTools::BumaTosrcma(const QByteArray &data)
{

    QList<QPointF> listPoint;
    quint16 shortData = 0;
    qint16 tempData = 0;
    quint16 mask = 0;
    qint32 j = 0;

    for(qint32 i = 0; i < data.size()-1; i+=2)
    {
         shortData = 0;
         shortData = ((quint8)data.at(i)<<8);
         shortData |= (quint8)data.at(i+1)&0xFF;
         mask = shortData & (1<<15);
         tempData = mask?((shortData^0xFFFF)-1)*(-1):shortData;
         listPoint.append(QPointF(j,tempData));
         j++;
    }
    return listPoint;
}
