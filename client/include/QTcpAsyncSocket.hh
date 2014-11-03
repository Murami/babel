#ifndef QTCP_ASYNC_SOCKET_HH
#define QTCP_ASYNC_SOCKET_HH

#include <QtNetwork>
#include <QObject>
#include <QHostAddress>
#include <QtGlobal>

#include <iostream>

#include "IAsyncSocketListener.hh"

class QTcpAsyncSocket : public IAsyncSocketListener
{
Q_OBJECT

public:
  QTcpAsyncSocket();
  ~QTcpAsyncSocket();

  void connect(QString address, quint16 port);
  void disconnect();
  void read();
  void write(void *data);
  QHostAddress & getAddress();
  quint16 & getPort();
  quint64 bytesAvailable ();

public slots:
  void onConnect();
  void onDisconnect();
  void onError(QAbstractSocket::SocketError error);
  void onRead();

signals:
  void notifyConnect();
  void notifyDisconnect();
  void notifyError(QAbstractSocket::SocketError error);
  void notifyRead();

private:
  QTcpSocket m_socket;
  QHostAddress m_address;
  quint16 m_port;
};

#endif
