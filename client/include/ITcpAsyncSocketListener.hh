#ifndef I_TCP_ASYNC_SOCKET_LISTENER
#define I_TCP_ASYNC_SOCKET_LISTENER

#include <QtNetwork>

class ITcpAsyncSocketListener
{
public:
  virtual void onConnect() = 0;
  virtual void onDisconnect() = 0;
  virtual void onError(QAbstractSocket::SocketError erreur) = 0;
  virtual void onRead() = 0;
};

#endif
