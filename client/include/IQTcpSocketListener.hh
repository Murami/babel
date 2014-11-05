#ifndef I_QTCP_SOCKET_LISTENER_HH
#define I_QTCP_SOCKET_LISTENER_HH

#include <QObject>
#include <QAbstractSocket>

class IQTcpSocketListener : public QObject
{
Q_OBJECT

public slots:
  virtual void			onConnect() = 0;
  virtual void			onDisconnect() = 0;
  virtual void			onError(int error) = 0;
  virtual void			onRead() = 0;
};

#endif
