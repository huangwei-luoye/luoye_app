#include <qplatformdefs.h>
#include <QtGui/5.8.0/QtGui/qpa/qwindowsysteminterface.h>
#include <QtGui/QGuiApplication>
#include "QEventDispatcherLibuvGui.h"

QEventDispatcherLibuvGui::QEventDispatcherLibuvGui(QObject* parent)
    : QEventDispatcherLibuv(parent)
{
}

QEventDispatcherLibuvGui::~QEventDispatcherLibuvGui(void)
{
}

bool QEventDispatcherLibuvGui::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    bool sent_events = QWindowSystemInterface::sendWindowSystemEvents(flags);
    if (QEventDispatcherLibuv::processEvents(flags))
    {
        return true;
    }
    return sent_events;
}

bool QEventDispatcherLibuvGui::hasPendingEvents(void)
{
    return (QEventDispatcherLibuv::hasPendingEvents()
            || QWindowSystemInterface::windowSystemEventsQueued());
}

void QEventDispatcherLibuvGui::flush(void)
{
    if (qApp)
    {
        qApp->sendPostedEvents();
    }
}
