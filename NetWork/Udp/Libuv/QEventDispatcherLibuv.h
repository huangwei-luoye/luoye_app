#ifndef QEVENTDISPATCHER_LIBUV_H
#define QEVENTDISPATCHER_LIBUV_H

#include <QtCore/QAbstractEventDispatcher>

class QEventDispatcherLibuvPrivate;
class QEventDispatcherLibuv : public QAbstractEventDispatcher
{
    Q_OBJECT
public:
    explicit QEventDispatcherLibuv(QObject* parent = 0);
    virtual ~QEventDispatcherLibuv(void);

    virtual bool processEvents(QEventLoop::ProcessEventsFlags flags);
    virtual bool hasPendingEvents(void);

    virtual void registerSocketNotifier(QSocketNotifier* notifier);
    virtual void unregisterSocketNotifier(QSocketNotifier* notifier);

    virtual void registerTimer(
        int timerId,
        int interval,
#if QT_VERSION >= 0x050000
        Qt::TimerType timerType,
#endif
        QObject* object
    );

    virtual bool unregisterTimer(int timerId);
    virtual bool unregisterTimers(QObject* object);
    virtual QList<QAbstractEventDispatcher::TimerInfo> registeredTimers(QObject* object) const;
#if QT_VERSION >= 0x050000
    virtual int remainingTime(int timerId);
#endif

#if defined(Q_OS_WIN) && QT_VERSION >= 0x050000
    virtual bool registerEventNotifier(QWinEventNotifier* notifier);
    virtual void unregisterEventNotifier(QWinEventNotifier* notifier);
#endif

    virtual void wakeUp(void);
    virtual void interrupt(void);
    virtual void flush(void);

    void* currentLoop() const;

protected:
    QEventDispatcherLibuv(QEventDispatcherLibuvPrivate& dd, QObject* parent = 0);

private:
    Q_DISABLE_COPY(QEventDispatcherLibuv)
    Q_DECLARE_PRIVATE(QEventDispatcherLibuv)
#if QT_VERSION >= 0x040600
    QScopedPointer<QEventDispatcherLibuvPrivate> d_ptr;
#else
    EventDispatcherLibUvPrivate* d_ptr;
#endif
};

#endif // QEVENTDISPATCHER_LIBUV_H
