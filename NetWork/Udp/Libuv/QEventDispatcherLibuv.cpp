#include <QtCore/QPair>
#include <QtCore/QSocketNotifier>
#include <QtCore/QThread>
#include "QEventDispatcherLibuv.h"
#include "QEventDispatcherLibuv_p.h"

QEventDispatcherLibuv::QEventDispatcherLibuv(QObject* parent)
    : QAbstractEventDispatcher(parent), d_ptr(new QEventDispatcherLibuvPrivate(this))
{
}

QEventDispatcherLibuv::~QEventDispatcherLibuv(void)
{
#if QT_VERSION < 0x040600
    delete this->d_ptr;
    this->d_ptr = 0;
#endif
}

bool QEventDispatcherLibuv::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    Q_D(QEventDispatcherLibuv);
    return d->processEvents(flags);
}

bool QEventDispatcherLibuv::hasPendingEvents(void)
{
    extern uint qGlobalPostedEventsCount();
    return qGlobalPostedEventsCount() > 0;
}

void QEventDispatcherLibuv::registerSocketNotifier(QSocketNotifier* notifier)
{
#ifndef QT_NO_DEBUG
    if (notifier->socket() < 0)
    {
        qWarning("QSocketNotifier: Internal error: sockfd < 0");
        return;
    }

    if ((notifier->thread() != thread())
        || (thread() != QThread::currentThread()))
    {
        qWarning("QSocketNotifier: socket notifiers cannot be enabled from another thread");
        return;
    }
#endif

    if (notifier->type() == QSocketNotifier::Exception)
    {
        return;
    }

    Q_D(QEventDispatcherLibuv);
    d->registerSocketNotifier(notifier);
}

void QEventDispatcherLibuv::unregisterSocketNotifier(QSocketNotifier* notifier)
{
#ifndef QT_NO_DEBUG
    if (notifier->socket() < 0)
    {
        qWarning("QSocketNotifier: Internal error: sockfd < 0");
        return;
    }

    if ((notifier->thread() != thread() )
        || (thread() != QThread::currentThread()))
    {
        qWarning("QSocketNotifier: socket notifiers cannot be disabled from anot"
                 "her thread");
        return;
    }
#endif

    // Short circuit, we do not support QSocketNotifier::Exception
    if (notifier->type() == QSocketNotifier::Exception)
    {
        return;
    }

    Q_D(QEventDispatcherLibuv);
    d->unregisterSocketNotifier(notifier);
}

void QEventDispatcherLibuv::registerTimer(
    int timerId,
    int interval,
#if QT_VERSION >= 0x050000
    Qt::TimerType timerType,
#endif
    QObject* object
)
{
#ifndef QT_NO_DEBUG
    if ((timerId < 1) || (interval < 0) || !object)
    {
        qWarning("%s: invalid arguments", Q_FUNC_INFO);
        return;
    }

    if ((object->thread() != this->thread())
        && (this->thread() != QThread::currentThread()) )
    {
        qWarning("%s: timers cannot be started from another thread", Q_FUNC_INFO);
        return;
    }
#endif

    Qt::TimerType type;
#if QT_VERSION >= 0x050000
    type = timerType;
#else
    type = Qt::CoarseTimer;
#endif

    Q_D(QEventDispatcherLibuv);
    if (interval)
    {
        d->registerTimer(timerId, interval, type, object);
    }
    else
    {
        d->registerZeroTimer(timerId, object);
    }
}

bool QEventDispatcherLibuv::unregisterTimer(int timerId)
{
#ifndef QT_NO_DEBUG
    if (timerId < 1)
    {
        qWarning("%s: invalid arguments", Q_FUNC_INFO);
        return false;
    }

    if (this->thread() != QThread::currentThread())
    {
        qWarning("%s: timers cannot be stopped from another thread", Q_FUNC_INFO);
        return false;
    }
#endif

    Q_D(QEventDispatcherLibuv);
    return d->unregisterTimer(timerId);
}

bool QEventDispatcherLibuv::unregisterTimers(QObject* object)
{
#ifndef QT_NO_DEBUG
    if (!object)
    {
        qWarning("%s: invalid arguments", Q_FUNC_INFO);
        return false;
    }

    if ((object->thread() != this->thread())
        && (this->thread() != QThread::currentThread()))
    {
        qWarning("%s: timers cannot be stopped from another thread", Q_FUNC_INFO);
        return false;
    }
#endif

    Q_D(QEventDispatcherLibuv);
    return d->unregisterTimers(object);
}

QList<QAbstractEventDispatcher::TimerInfo> QEventDispatcherLibuv::registeredTimers(QObject* object) const
{
    if (!object)
    {
        qWarning("%s: invalid argument", Q_FUNC_INFO);
        return QList<QAbstractEventDispatcher::TimerInfo>();
    }

    Q_D(const QEventDispatcherLibuv);
    return d->registeredTimers(object);
}

#if QT_VERSION >= 0x050000
int QEventDispatcherLibuv::remainingTime(int timerId)
{
    Q_D(const QEventDispatcherLibuv);
    return d->remainingTime(timerId);
}
#endif

#if defined(Q_OS_WIN) && QT_VERSION >= 0x050000
bool QEventDispatcherLibuv::registerEventNotifier(QWinEventNotifier* notifier)
{
    Q_UNUSED(notifier)
    Q_UNIMPLEMENTED();
    return false;
}

void QEventDispatcherLibuv::unregisterEventNotifier(QWinEventNotifier* notifier)
{
    Q_UNUSED(notifier)
    Q_UNIMPLEMENTED();
}
#endif

void QEventDispatcherLibuv::wakeUp(void)
{
    Q_D(QEventDispatcherLibuv);

#if QT_VERSION >= 0x040400
    if (d->m_wakeups.testAndSetAcquire(0, 1))
#endif
    {
        uv_async_send(&d->m_wakeup);
    }
}

void QEventDispatcherLibuv::interrupt(void)
{
    Q_D(QEventDispatcherLibuv);
    d->m_interrupt = true;
    this->wakeUp();
}

void QEventDispatcherLibuv::flush(void)
{
}

void* QEventDispatcherLibuv::currentLoop() const
{
    return d_ptr->m_base;
}

QEventDispatcherLibuv::QEventDispatcherLibuv(QEventDispatcherLibuvPrivate& dd, QObject* parent)
    : QAbstractEventDispatcher(parent), d_ptr(&dd)
{
}
