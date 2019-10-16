#include "CWaitObject.h"
#include <stdio.h>
CWaitObject::CWaitObject(int nID, QObject *parent)
    :QObject(parent)
{
    m_nID = nID;
    m_nInterval = 1000;
    m_isOK = false;
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    m_timer.setSingleShot(true);
}

CWaitObject::~CWaitObject()
{
    if (m_loop.isRunning())
    {
        m_loop.exit(false);
    }
}

void CWaitObject::setInterval(int ms)
{
    m_nInterval = ms;
}

bool CWaitObject::wait()
{
    if (!m_isOK)
    {
        m_timer.setInterval(m_nInterval); 
        m_timer.start();
        return m_loop.exec();
    }
    return true;
}

bool CWaitObject::wait(int ms)
{
    if (!m_isOK)
    {
        m_timer.setInterval(ms);
        m_timer.start();
        return m_loop.exec();
    }
    return true;
}

void CWaitObject::wake()
{
    m_isOK = true;
    m_timer.stop();
    m_loop.exit(true);
}

int CWaitObject::getID() const
{
    return m_nID;
}

void CWaitObject::slotTimeout()
{
    m_loop.exit(false);
}
