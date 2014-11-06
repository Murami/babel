#ifndef I_QUDP_SOCKET_LISTENER_HH
#define I_QUDP_SOCKET_LISTENER_HH

#include <QObject>
#include <QAbstractSocket>

class IQUdpSocketListener : public QObject
{
Q_OBJECT

public slots:
  virtual void		onError(QAbstractSocket::SocketError error) = 0;
  virtual void		onRead() = 0;
};

#endif
