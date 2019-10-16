#include "ExperimentFileOperat.h"
#include "LogOpreate/LogOperate.h"
#include <QTime>
#include <QDebug>

#define SAVE_PATH "./RecvData/"
ExperimentFileOperat::ExperimentFileOperat(QObject *parent) :
    QObject(parent)
{
    this->moveToThread(&m_WorkThread);
    m_WorkThread.start();
}

ExperimentFileOperat::~ExperimentFileOperat()
{
    QMap<quint8, QFile*> ::iterator it;
    for(it = m_FileMap.begin(); it!=m_FileMap.begin(); ++it)
    {
       QFile *pFile = it.value();
       if(pFile && pFile->isOpen())
       {
           pFile->close();
           delete pFile;
           pFile = nullptr;
       }
    }
    m_FileMap.clear();
    m_WorkThread.quit();
    m_WorkThread.wait();
}

void ExperimentFileOperat::OnOperatResultData(quint8 channel, const QByteArray &data, bool isEnd)
{

    if(m_FileMap.contains(channel))
    {
        QFile *pFile = m_FileMap.value(channel);
        if(pFile && pFile->isOpen())
        {
            pFile->write(data);
            pFile->flush();
        }
        if(isEnd)
        {
            if(pFile && pFile->isOpen())
            {
                pFile->close();
                delete pFile;
                pFile = nullptr;

                emit OperatFinishSignal(channel);
                LogOperate::getinstance()->LogOperaterUi(QString("通道%1采存数据写入完成").arg(channel));
                m_FileMap.remove(channel);
            }
        }
    }
    else
    {
        QFile *pFile = new QFile;
        QDateTime DateTime = QDateTime::currentDateTime();
        QString strDateTime = DateTime.toString("yyyy_MM_dd.hh_mm_ss");
        QString strFileName = QString(SAVE_PATH) + strDateTime + QString(".dat");

        pFile->setFileName(strFileName);
        if(pFile->open(QIODevice::WriteOnly))
        {
            pFile->write(data);
            pFile->flush();
            m_FileMap.insert(channel, pFile);

            if(isEnd)
            {
                if(pFile && pFile->isOpen())
                {
                    pFile->close();
                    delete pFile;
                    pFile = nullptr;

                    emit OperatFinishSignal(channel);
                    qDebug()<<"fa song xignhao ";
                    LogOperate::getinstance()->LogOperaterUi(QString("通道%1采存数据写入完成").arg(channel));
                    m_FileMap.remove(channel);
                }
            }
        }
        else
        {
            LogOperate::getinstance()->LogOperaterUi(QString("打开文件失败！ " + pFile->fileName()),LOG_ERROR);
        }
     }

}
