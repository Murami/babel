#ifndef I_ASYNC_SOCKET_LISTENER
#define I_ASYNC_SOCKET_LISTENER

#include <QtNetwork>
#include <QObject>

class IAsyncSocketListener : public QObject
{
Q_OBJECT

public slots:
  virtual void onConnect() = 0;
  virtual void onDisconnect() = 0;
  virtual void onError(QAbstractSocket::SocketError erreur) = 0;
  virtual void onRead() = 0;
};

#endif
