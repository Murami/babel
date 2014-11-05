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
  m_address.setAddress(QString::fromUtf8(address.c_str()));
  m_port = port;
  m_socket.abort();
  m_socket.connectToHost(m_address, m_port);
}

void TcpAsyncSocket::disconnect()
{
  if (m_socket.isValid())
    m_socket.disconnectFromHost();
  else
    m_socket.abort();
}

void TcpAsyncSocket::read(char * data, qint64 maxSize)
{
  std::cout << "\033[34m[ client ]\tReading data from server\033[0m" << std::endl;
  m_socket.read(data, maxSize);
}

void TcpAsyncSocket::write(void *data)
{
  m_socket.write(reinterpret_cast<const char*>(const_cast<void*>(data)));
}

void TcpAsyncSocket::write(void *data, qint64 size)
{
  m_socket.write(reinterpret_cast<const char*>(const_cast<void*>(data)), size);
}

QHostAddress & TcpAsyncSocket::getAddress()
{
  return (m_address);
}

quint16 & TcpAsyncSocket::getPort()
{
  return (m_port);
}

quint64 TcpAsyncSocket::bytesAvailable()
{
  return (m_socket.bytesAvailable());
}

/* listened socket event */

void TcpAsyncSocket::onConnect()
{
  std::cout << "connect detected" << std::endl;
  notifyConnect();
}

void TcpAsyncSocket::onDisconnect()
{
  std::cout << "disconnect detected" << std::endl;
  notifyDisconnect();
}

void TcpAsyncSocket::onError(QAbstractSocket::SocketError error)
{
  std::cout << "error detected" << std::endl;
  notifyError(error);
}

void TcpAsyncSocket::onRead()
{
  std::cout << "data ready to read" << std::endl;
  notifyRead();
}

/* listener control */

void TcpAsyncSocket::notifyConnect()
{
  std::list<ITcpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onConnect();
}

void TcpAsyncSocket::notifyDisconnect()
{
  std::list<ITcpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onDisconnect();
}

void TcpAsyncSocket::notifyError(QAbstractSocket::SocketError error)
{
  std::list<ITcpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onError(error);
}

void TcpAsyncSocket::notifyRead()
{
  std::list<ITcpAsyncSocketListener *>::iterator it;

  it = m_listenerList.begin();
  for (; it != m_listenerList.end(); ++it)
    (*it)->onRead();
}

void TcpAsyncSocket::addListener(ITcpAsyncSocketListener * listener)
{
  m_listenerList.push_front(listener);
}
