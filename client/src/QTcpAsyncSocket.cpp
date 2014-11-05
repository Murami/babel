#include "Protocol.hh"
#include "QTcpAsyncSocket.hh"

QTcpAsyncSocket::QTcpAsyncSocket()
{
  QObject::connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));
  QObject::connect(&m_socket, SIGNAL(connected()), this, SLOT(onConnect()));
  QObject::connect(&m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
  QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

QTcpAsyncSocket::~QTcpAsyncSocket()
{

}

void QTcpAsyncSocket::connect(QString address, quint16 port)
{
  m_address.setAddress(address);
  m_port = port;
  m_socket.abort();
  m_socket.connectToHost(m_address, m_port);
}

void QTcpAsyncSocket::disconnect()
{
  if (m_socket.isValid())
    m_socket.disconnectFromHost();
  else
    m_socket.abort();
}

void QTcpAsyncSocket::read(char * data, qint64 maxSize)
{
  std::cout << "\033[34m[ client ]\tReading data from server\033[0m" << std::endl;
  m_socket.read(data, maxSize);
}

void QTcpAsyncSocket::write(void *data)
{
  m_socket.write(reinterpret_cast<const char*>(const_cast<void*>(data)));
}

void QTcpAsyncSocket::write(void *data, qint64 size)
{
  m_socket.write(reinterpret_cast<const char*>(const_cast<void*>(data)), size);
}

QHostAddress & QTcpAsyncSocket::getAddress()
{
  return (m_address);
}

quint16 & QTcpAsyncSocket::getPort()
{
  return (m_port);
}

quint64 QTcpAsyncSocket::bytesAvailable()
{
  return (m_socket.bytesAvailable());
}

void QTcpAsyncSocket::onConnect()
{
  std::cout << "connect detected" << std::endl;
  emit notifyConnect();
}

void QTcpAsyncSocket::onDisconnect()
{
  std::cout << "disconnect detected" << std::endl;
  emit notifyDisconnect();
}

void QTcpAsyncSocket::onError(QAbstractSocket::SocketError error)
{
  std::cout << "error detected" << std::endl;
  emit notifyError(error);
}

void QTcpAsyncSocket::onRead()
{
  std::cout << "data ready to read" << std::endl;
  emit notifyRead();
}
