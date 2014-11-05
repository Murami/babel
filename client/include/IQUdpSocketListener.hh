#ifndef I_QUDP_SOCKET_LISTENER_HH
#define I_QUDP_SOCKET_LISTENER_HH

#include <QObject>

class IQUdpSocketListener : public QObject
{
Q_OBJECT

public slots:
  virtual void		onError(int error) = 0;
  virtual void		onRead() = 0;
};

#endif
