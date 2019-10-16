#ifndef CTOOLS_H
#define CTOOLS_H
#include <QString>
#include <QList>
#include <QPointF>

class CTools
{
public:
    CTools();

    static QString ByteArrayToString(const QByteArray &data);
    static void Delay(quint32 ms);
    static QList<QPointF> BumaTosrcma(const QByteArray &data);
};

#endif // CTOOLS_H
