#include "CWaitObjectManager.h"

#include "CWaitObject.h"

CWaitObjectManager::CWaitObjectManager()
{

}

CWaitObjectManager::~CWaitObjectManager()
{
    clear();
}

void CWaitObjectManager::push(int id)
{
    if (!contains(id))
    {
        m_items.append(new CWaitObject(id));
    }
}

void CWaitObjectManager::push(int id, int ms)
{
    if (!contains(id))
    {
        CWaitObject *pObj = new CWaitObject(id);
        pObj->setInterval(ms);
        m_items.append(pObj);
    }
}

bool CWaitObjectManager::waitAll(int ms)
{
    bool bRet = false;
    for (int i=0; i<m_items.length(); ++i)
    {
        CWaitObject *pObj = m_items.at(i);
        if (pObj)
        {
            bRet = pObj->wait(ms);
            if (!bRet)
            {
                break;
            }
        }
    }
    clear();
    return bRet;
}

bool CWaitObjectManager::waitAll()
{
    bool bRet = false;
    for (int i=0; i<m_items.length(); ++i)
    {
        CWaitObject *pObj = m_items.at(i);
        if (pObj)
        {
            bRet = pObj->wait();
            if (!bRet)
            {
                break;
            }
        }
    }
    clear();
    return bRet;
}

void CWaitObjectManager::wakeOne(int id)
{
    CWaitObject *pObj = getObjectByID(id);
    if (pObj)
    {
        pObj->wake();
    }
}

void CWaitObjectManager::wakeAll()
{
    for (int i=0; i<m_items.length(); ++i)
    {
        CWaitObject *pObj = m_items.at(i);
        if (pObj)
        {
            pObj->wake();
        }
    }
}

void CWaitObjectManager::clear()
{
    while (m_items.length() > 0)
    {
        CWaitObject *pObj = m_items.takeFirst();
        if (pObj)
        {
            delete pObj;
        }
    }
}

bool CWaitObjectManager::contains(int id)
{
    return (getObjectByID(id) != nullptr);
}

CWaitObject *CWaitObjectManager::getObjectByID(int id)
{
    CWaitObject *pRet = nullptr;
    for (int i=0; i<m_items.length(); ++i)
    {
        CWaitObject *pObj = m_items.at(i);
        if (pObj && (pObj->getID() == id))
        {
            pRet = pObj;
            break;
        }
    }
    return pRet;
}

CWaitObject *CWaitObjectManager::getObjectByIndex(int index)
{
    CWaitObject *pRet = nullptr;

    if ((index >= 0) && (index < m_items.length()))
    {
        pRet = m_items.at(index);
    }
    return pRet;
}
