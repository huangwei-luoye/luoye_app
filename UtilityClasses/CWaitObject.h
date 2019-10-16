#ifndef CWAITOBJECT_H
#define CWAITOBJECT_H

#include <QEventLoop>
#include <QObject>
#include <QTimer>

class CWaitObject : public QObject
{
    Q_OBJECT
public:
    explicit CWaitObject(int nID, QObject *parent = nullptr);
    virtual ~CWaitObject();

public:
    void    setInterval(int ms);
    bool    wait();
    bool    wait(int ms);
    void    wake();

    int     getID() const;

private slots:
    void    slotTimeout();

private:
    int         m_nID;
    bool        m_bNeedDestory;
    int         m_nInterval;
    bool        m_isOK;
    QTimer      m_timer;
    QEventLoop  m_loop;

};

#endif // CWAITOBJECT_H
