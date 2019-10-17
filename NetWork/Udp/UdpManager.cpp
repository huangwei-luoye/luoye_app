#include "UdpManager.h"
#include "UvUdpSocket.h"
#include "Libuv/QEventDispatcherLibuv.h"
#include "Libuv/uv.h"

UdpManager::UdpManager()
{
    uvThread = new QThread;
    uvThread->setEventDispatcher(new QEventDispatcherLibuv);
    uvThread->start();
}

UdpManager::~UdpManager()
{
    uvThread->quit();
    uvThread->deleteLater();
}

UdpManager& UdpManager::instance()
{
    static UdpManager manager;
    return manager;
}

QSharedPointer<UvUdpSocket> UdpManager::findSocket(const QString& addr, quint16 port)
{
    QMutexLocker locker(&mutex);
    SocketAddr socketAddr = qMakePair(addr, port);
    QSharedPointer<UvUdpSocket> socket = sockets[socketAddr].toStrongRef();
    if (!socket)
    {
        socket = QSharedPointer<UvUdpSocket>(new UvUdpSocket(addr, port),
                                             [](UvUdpSocket* socket){socket->deleteLater();});
        initSocket(socket);
        sockets.insert(socketAddr, socket.toWeakRef());
    }
    return socket;
}

void UdpManager::initSocket(QSharedPointer<UvUdpSocket>& socket)
{
    socket->moveToThread(uvThread);
    QTimer::singleShot(0, socket.data(), SLOT(init()));
}
