#include "UdpAsyncSocket.hh"
#include "IUdpAsyncSocketListener.hh"

UdpAsyncSocket::UdpAsyncSocket()
{
}

UdpAsyncSocket::~UdpAsyncSocket()
{

}

void	UdpAsyncSocket::connectToHost(const std::string& host, qint16 port)
{
  m_socket.connectToHost(host.c_str(), port);
  QObject::connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));
  QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

bool	UdpAsyncSocket::bind(std::string & address, uint16_t port)
{
  QHostAddress	addr;
  bool		ret;

  addr.setAddress(QString::fromUtf8(address.c_str()));
  ret = m_socket.bind(QHostAddress::Any, port);
  QObject::connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));
  QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

  return (ret);
}

void	UdpAsyncSocket::close()
{
  m_socket.close();
}

bool	UdpAsyncSocket::bind(uint16_t port = 0)
{
  bool	ret;

  ret =  m_socket.bind(port, QUdpSocket::ShareAddress);
  QObject::connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));
  QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

  return (ret);
}

bool	UdpAsyncSocket::hasPendingDatagrams() const
{
  return (m_socket.hasPendingDatagrams());
}

int64_t	UdpAsyncSocket::pendingDatagramSize() const
{
  return (m_socket.pendingDatagramSize());
}

int64_t	UdpAsyncSocket::readDatagram(void * data, int64_t maxSize, std::string * address, uint16_t * port)
{
  QHostAddress	addr;
  std::string	tmp;
  int64_t	size;

  if (address != NULL)
    {
      size = m_socket.readDatagram(static_cast<char*>(data), maxSize, &addr, port);
      tmp = addr.toString().toStdString();
      *address = tmp;
      return (size);
    }
  else
    return (m_socket.readDatagram(static_cast<char*>(data), maxSize, NULL, port));
}

int64_t	UdpAsyncSocket::writeDatagram(const void * data, int64_t size, std::string & address, uint16_t port)
{
  QHostAddress                          addr;

  addr.setAddress(QString::fromUtf8(address.c_str()));
  return (m_socket.writeDatagram(static_cast<char*>(const_cast<void*>(data)), size, addr, port));
}

void	UdpAsyncSocket::onError(QAbstractSocket::SocketError error)
{
  notifyError(error);
}

void	UdpAsyncSocket::onRead()
{
  std::cout << "\033[41monRead\033[0m\n";
  notifyRead();
}

void	UdpAsyncSocket::addListener(IUdpAsyncSocketListener * listener)
{
  m_listenerList.push_front(listener);
}

void	UdpAsyncSocket::notifyError(int error)
{
  std::list<IUdpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onUdpError(error);
}

void	UdpAsyncSocket::notifyRead()
{
  std::list<IUdpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onUdpRead();
}
