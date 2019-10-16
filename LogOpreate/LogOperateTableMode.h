#ifndef LOGOPERATETABLEMODE_H
#define LOGOPERATETABLEMODE_H

#include <QAbstractTableModel>
#include <QDateTime>
#include <QList>
#include <QVariant>
#include "LogOperate.h"

struct LogOperateData
{
    LogOperateLevel logLevel;
    QDateTime dateTime;
    QString logMsg;

    LogOperateData() :
        logLevel(LOG_INFO),
        dateTime(QDateTime()),
        logMsg("")
    {
        // null
    }

    LogOperateData(const LogOperateLevel &logLevel,
            const QDateTime &dateTime,
            const QString &logMsg) :
        logLevel(logLevel),
        dateTime(dateTime),
        logMsg(logMsg)
    {
        // null
    }
};

class LogOperateTableMode : public QAbstractTableModel
{
    Q_OBJECT

public:
    LogOperateTableMode(QObject *parent = nullptr);
    ~LogOperateTableMode(void);

public:
    void addRowData(LogOperateData *data);
    void removeRowData(int row);
    void clearData();

protected:
    virtual int	columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int	rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<LogOperateData *> m_lstDatas;
};

#endif // LOGOPERATETABLEMODE_H
