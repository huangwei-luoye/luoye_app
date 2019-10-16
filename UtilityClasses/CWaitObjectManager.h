#ifndef CWAITOBJECTMANAGER_H
#define CWAITOBJECTMANAGER_H

#include <QList>

class CWaitObject;

class CWaitObjectManager
{
public:
    explicit CWaitObjectManager();
    virtual ~CWaitObjectManager();

public:
    void    push(int id);
    void    push(int id, int ms);
    bool    waitAll();
    bool    waitAll(int ms);
    void    wakeOne(int id);
    void    wakeAll();
    void    clear();


    bool        contains(int id);
private:
    CWaitObject *getObjectByID(int id);
    CWaitObject *getObjectByIndex(int index);

private:
    QList<CWaitObject*> m_items;
};

#endif // CWAITOBJECTMANAGER_H
