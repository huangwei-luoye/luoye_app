#ifndef LOGOPERATEFILE_H
#define LOGOPERATEFILE_H

#include <QObject>
#include <QFile>

#define LOG_PATH "./log/"

// 打印日志等级
enum LogOperateLevel
{
    LOG_INFO = 0,       // 常规提示信息
    LOG_WARNING,        // 警告信息
    LOG_ERROR,          // 错误信息
};

class LogOperate : public QObject
{
    Q_OBJECT

public:
    LogOperate();
    virtual ~LogOperate();

    static LogOperate* getinstance();
    /**
     * @brief LogOperateFile
     * @param log
     * 将日志数据写入到文件中
     */
    void LogOperateFile(const QString& log);
    /**
     * @brief LogOperaterUi 打印日志事件处理
     * @param log   打印信息
     * @param level 日志等级
     */
    void LogOperaterUi(const QString& log, LogOperateLevel level=LOG_INFO);

private:
    QFile m_fileRecord;

    Q_SLOT void OnLogOperateFile(const QString& log);
    Q_SIGNAL void LogOperateFileSignal(const QString& log);
    Q_SIGNAL void LogOperateUiSignal(const QString& log, LogOperateLevel level);
};

#endif // LOGOPERATEFILE_H
