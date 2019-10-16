#ifndef CQSSFILEADAPTION_H
#define CQSSFILEADAPTION_H

#include <QString>

class CQssFileAdaption
{
public:
    CQssFileAdaption();
    virtual ~CQssFileAdaption();

    static CQssFileAdaption* getInstance();

    void SetAdaption(const QString& adaption);

    QString getMainWindow();
    QString getLog();
    QString getCommunication();

};

#endif // CQSSFILEADAPTION_H
