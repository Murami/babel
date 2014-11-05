#ifndef TCP_ASYNC_SOCKET_HH
#define TCP_ASYNC_SOCKET_HH

#include <QtNetwork>
#include <QObject>
#include <QHostAddress>
#include <QtGlobal>

#include <stdint.h>
#include <iostream>

#include "IQTcpSocketListener.hh"

class ITcpAsyncSocketListener;

class TcpAsyncSocket : public IQTcpSocketListener
{
Q_OBJECT

public:
  TcpAsyncSocket();
  ~TcpAsyncSocket();

  void			connect(std::string address, uint16_t port);
  void			disconnect();
  void			read(char * data, qint64 maxSize);
  void			write(void *data);
  void			write(void *data, qint64 size);
  QHostAddress &	getAddress();
  quint16 &		getPort();
  quint64		bytesAvailable ();

public slots:
  void			onConnect();
  void			onDisconnect();
  void			onError(QAbstractSocket::SocketError error);
  void			onRead();

public:
  void			addListener(ITcpAsyncSocketListener * listener);

private:
  void			notifyConnect();
  void			notifyDisconnect();
  void			notifyError(QAbstractSocket::SocketError error);
  void			notifyRead();


private:
  std::list<ITcpAsyncSocketListener *>	m_listenerList;
  QTcpSocket				m_socket;
  QHostAddress				m_address;
  quint16				m_port;
};

#endif
