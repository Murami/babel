#ifndef UDP_ASYNC_SOCKET_HH
#define UDP_ASYNC_SOCKET_HH

#include <QtNetwork>
#include <QObject>
#include <stdint.h>
#include <iostream>

#include "IQUdpSocketListener.hh"

class IUdpAsyncSocketListener;

class UdpAsyncSocket : public IQUdpSocketListener
{
Q_OBJECT

public:
  UdpAsyncSocket();
  ~UdpAsyncSocket();

  bool		bind(std::string & address, uint16_t port);
  bool		bind(uint16_t port);
  bool		hasPendingDatagrams() const;
  int64_t	pendingDatagramSize() const;
  int64_t	readDatagram(char * data, int64_t maxSize, std::string * address = NULL, uint16_t * port = NULL);
  int64_t	writeDatagram(const char * data, int64_t size, std::string & address, uint16_t port);

public slots:
  void		onError(QAbstractSocket::SocketError error);
  void		onRead();

public:
  void		addListener(IUdpAsyncSocketListener * listener);

private:
  void		notifyError(int error);
  void		notifyRead();

private:
  std::list<IUdpAsyncSocketListener *>	m_listenerList;
  QUdpSocket				m_socket;

};

#endif
