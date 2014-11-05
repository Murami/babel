#ifndef TCP_ASYNC_SOCKET_HH
#define TCP_ASYNC_SOCKET_HH

#include <QtNetwork>
#include <QObject>
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
  void			read(char * data, int64_t maxSize);
  void			write(void *data);
  void			write(void *data, int64_t size);
  std::string &		getAddress();
  uint16_t &		getPort();
  uint64_t		bytesAvailable();

public slots:
  void			onConnect();
  void			onDisconnect();
  void			onError(int error);
  void			onRead();

public:
  void			addListener(ITcpAsyncSocketListener * listener);

private:
  void			notifyConnect();
  void			notifyDisconnect();
  void			notifyError(int error);
  void			notifyRead();


private:
  std::list<ITcpAsyncSocketListener *>	m_listenerList;
  QTcpSocket				m_socket;
  std::string				m_address;
  uint16_t				m_port;
};

#endif
