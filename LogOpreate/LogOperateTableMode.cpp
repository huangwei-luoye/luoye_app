#include "LogOperateTableMode.h"
#include <QColor>
#include <QFont>
#include <QDebug>

LogOperateTableMode::LogOperateTableMode(QObject *parent) :
    QAbstractTableModel(parent)
{

}

LogOperateTableMode::~LogOperateTableMode()
{
    clearData();
}

void LogOperateTableMode::addRowData(LogOperateData *data)
{
    beginResetModel();

    m_lstDatas.append(data);

    endResetModel();
}

void LogOperateTableMode::removeRowData(int row)
{
    if ((row < 0) || (row > m_lstDatas.size()))
    {
        return;
    }

    beginResetModel();

    m_lstDatas.removeAt(row);

    endResetModel();
}

void LogOperateTableMode::clearData()
{
    beginResetModel();

    foreach (LogOperateData *data, m_lstDatas)
    {
        delete data;
    }
    m_lstDatas.clear();

    endResetModel();
}

int LogOperateTableMode::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

int LogOperateTableMode::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_lstDatas.size();
}

QVariant LogOperateTableMode::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_lstDatas.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        const LogOperateData *logData = m_lstDatas.at(index.row());

        if (index.column() == 0)
        {
            return logData->dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
        }
        else if (index.column() == 1)
        {
            return logData->logMsg;
        }
    }
    else if (role == Qt::BackgroundRole)
    {
        if(index.row()%2 == 0)
        {
            return QColor(50, 138, 201, 50);
        }

        return QColor(44, 112, 161, 100);
    }
    else if ((role == Qt::TextAlignmentRole) && (index.column() == 0))
    {
        return Qt::AlignCenter;
    }
    else if(role == Qt::TextColorRole)
    {
        const LogOperateData *logData = m_lstDatas.at(index.row());
        switch (logData->logLevel)
        {
            case LOG_WARNING:
            {
                return QColor(Qt::yellow);
            }
            case LOG_ERROR:
            {
                return QColor(Qt::red);
            }
            default:
                return QColor(255, 255, 255);
        }
    }

    return QVariant();
}

QVariant LogOperateTableMode::headerData(int section,
                                Qt::Orientation orientation,
                                int role) const
{
    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return "时间/日期";
            case 1:
                return "日志";
        }

    }

    return QVariant();
}
