#include "UdpAsyncSocket.hh"
#include "IUdpAsyncSocketListener.hh"

UdpAsyncSocket::UdpAsyncSocket()
{
  QObject::connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));;
  QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

UdpAsyncSocket::~UdpAsyncSocket()
{

}

bool	UdpAsyncSocket::bind(std::string & address, uint16_t port)
{
  QHostAddress	addr;

  addr.setAddress(QString::fromUtf8(address.c_str()));
  return (m_socket.bind(addr, port));
}

bool	UdpAsyncSocket::bind(uint16_t port = 0)
{
  return (m_socket.bind(port));
}

bool	UdpAsyncSocket::hasPendingDatagrams() const
{
  return (m_socket.hasPendingDatagrams());
}

int64_t	UdpAsyncSocket::pendingDatagramSize() const
{
  return (m_socket.pendingDatagramSize());
}

int64_t	UdpAsyncSocket::readDatagram(char * data, int64_t maxSize, std::string * address, uint16_t * port)
{
  QHostAddress	addr;
  std::string	tmp;
  int64_t	size;

  if (address != NULL)
    {
      size = m_socket.readDatagram(data, maxSize, &addr, port);
      tmp = addr.toString().toStdString();
      *address = tmp;
      return (size);
    }
  else
    return (m_socket.readDatagram(data, maxSize, NULL, port));
}

int64_t	UdpAsyncSocket::writeDatagram(const char * data, int64_t size, std::string & address, uint16_t port)
{
  QHostAddress                          addr;

  addr.setAddress(QString::fromUtf8(address.c_str()));
  return (m_socket.writeDatagram(data, size, addr, port));
}

void	UdpAsyncSocket::onError(int error)
{
  notifyError(error);
}

void	UdpAsyncSocket::onRead()
{
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
    (*it)->onError(error);
}

void	UdpAsyncSocket::notifyRead()
{
  std::list<IUdpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onRead();
}
