#ifndef QEVENTDISPATCHER_LIBUV_GUI_H
#define QEVENTDISPATCHER_LIBUV_GUI_H

#include "QEventDispatcherLibuv.h"

#if QT_VERSION < 0x050000
#	error This code requires at least Qt 5
#endif

class QEventDispatcherLibuvGui : public QEventDispatcherLibuv
{
    Q_OBJECT
public:
    explicit QEventDispatcherLibuvGui(QObject* parent = 0);
    virtual ~QEventDispatcherLibuvGui(void);

    bool processEvents(QEventLoop::ProcessEventsFlags flags) Q_DECL_OVERRIDE;
    bool hasPendingEvents(void) Q_DECL_OVERRIDE;
    void flush(void) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QEventDispatcherLibuvGui)
};

#endif // QEVENTDISPATCHER_LIBUV_GUI_H
