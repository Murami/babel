#include "Protocol.hh"
#include "TcpAsyncSocket.hh"
#include "ITcpAsyncSocketListener.hh"

TcpAsyncSocket::TcpAsyncSocket()
{
  QObject::connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));
  QObject::connect(&m_socket, SIGNAL(connected()), this, SLOT(onConnect()));
  QObject::connect(&m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
  QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

TcpAsyncSocket::~TcpAsyncSocket()
{

}

/* socket control */

void TcpAsyncSocket::connect(std::string address, uint16_t port)
{
  QHostAddress                          addr;

  addr.setAddress(QString::fromUtf8(address.c_str()));
  m_address = address;
  m_port = port;
  m_socket.abort();
  m_socket.connectToHost(addr, m_port);
}

void TcpAsyncSocket::disconnect()
{
  if (m_socket.isValid())
    m_socket.disconnectFromHost();
  else
    m_socket.abort();
}

void TcpAsyncSocket::read(char * data, int64_t maxSize)
{
  m_socket.read(data, maxSize);
}

void TcpAsyncSocket::write(void *data)
{
  m_socket.write(reinterpret_cast<const char*>(const_cast<void*>(data)));
}

void TcpAsyncSocket::write(void *data, int64_t size)
{
  m_socket.write(reinterpret_cast<const char*>(const_cast<void*>(data)), size);
}

std::string & TcpAsyncSocket::getAddress()
{
  return (m_address);
}

uint16_t & TcpAsyncSocket::getPort()
{
  return (m_port);
}

uint64_t TcpAsyncSocket::bytesAvailable()
{
  return (m_socket.bytesAvailable());
}

/* listened socket event */

void TcpAsyncSocket::onConnect()
{
  notifyConnect();
}

void TcpAsyncSocket::onDisconnect()
{
  notifyDisconnect();
}

void TcpAsyncSocket::onError(QAbstractSocket::SocketError error)
{
  notifyError(error);
}

void TcpAsyncSocket::onRead()
{
  notifyRead();
}

/* listener control */

void TcpAsyncSocket::notifyConnect()
{
  std::list<ITcpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onTcpConnect();
}

void TcpAsyncSocket::notifyDisconnect()
{
  std::list<ITcpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onTcpDisconnect();
  m_listenerList.clear();
}

void TcpAsyncSocket::notifyError(int error)
{
  std::list<ITcpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onTcpError(error);
}

void TcpAsyncSocket::notifyRead()
{
  std::list<ITcpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onTcpRead();
}

void TcpAsyncSocket::addListener(ITcpAsyncSocketListener * listener)
{
  m_listenerList.push_front(listener);
}
