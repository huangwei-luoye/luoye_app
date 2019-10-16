#include "LogOperate.h"

#include <QDir>
#include <QDateTime>

LogOperate::LogOperate()
{
    QDateTime DateTime = QDateTime::currentDateTime();
    QString strDateTime = DateTime.toString("yyyy_MM_dd.hh_mm_ss");
    QString strFileName = QString(LOG_PATH) + strDateTime + QString(".log");

    QDir dir = QDir::current();
    if(dir.mkpath(QString(LOG_PATH)))
    {
        dir.mkdir(QString(LOG_PATH));
    }
    m_fileRecord.setFileName(strFileName);
    m_fileRecord.open(QFile::WriteOnly | QFile::Text | QFile::Append);

    connect(this, SIGNAL(LogOperateFileSignal(QString)), this, SLOT(OnLogOperateFile(QString)), Qt::QueuedConnection);
}

LogOperate::~LogOperate()
{
    if(m_fileRecord.isOpen())
    {
        m_fileRecord.close();
    }
}

LogOperate *LogOperate::getinstance()
{
    static LogOperate instance;

    return &instance;
}

void LogOperate::LogOperateFile(const QString &log)
{
    emit LogOperateFileSignal(log);
}

void LogOperate::LogOperaterUi(const QString &log, LogOperateLevel level)
{
    emit LogOperateUiSignal(log, level);

    QString levelStr[] = {"【正常】", "【警告】", "【错误】"};
    LogOperateFile(log+levelStr[level]);
}

void LogOperate::OnLogOperateFile(const QString &log)
{
    QString strDateTime = QTime::currentTime().toString(QString("hh:mm:ss.zzz "));
    QString strTmp = strDateTime;
    strTmp += log;
    m_fileRecord.write(strTmp.toStdString().c_str());
    m_fileRecord.write(QString("\n").toStdString().c_str());
    m_fileRecord.flush();
}
