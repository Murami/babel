#include "BoostTcpAsyncClient.hh"
#include "BoostAsyncService.hh"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

BoostTcpAsyncClient::BoostTcpAsyncClient(BoostAsyncService& service) : m_socket(service.getIOService())
{
}

BoostTcpAsyncClient::~BoostTcpAsyncClient()
{
}

void	BoostTcpAsyncClient::readSome(char* buffer, size_t size)
{
  m_socket.async_read_some(boost::asio::buffer(buffer, size),
  			   boost::bind(&BoostTcpAsyncClient::onRead, this, buffer, size,
				       boost::asio::placeholders::bytes_transferred,
				       boost::asio::placeholders::error));
}

void	BoostTcpAsyncClient::writeSome(char* buffer, size_t size)
{
  m_socket.async_write_some(boost::asio::buffer(buffer, size),
			    boost::bind(&BoostTcpAsyncClient::onWrite, this, buffer,
					boost::asio::placeholders::bytes_transferred,
					boost::asio::placeholders::error));
}

void	BoostTcpAsyncClient::read(char* buffer, size_t size)
{
  boost::asio::async_read(m_socket, boost::asio::buffer(buffer, size),
			  boost::bind(&BoostTcpAsyncClient::onRead, this, buffer, size,
				      boost::asio::placeholders::bytes_transferred,
				      boost::asio::placeholders::error));
}

void	BoostTcpAsyncClient::write(char* buffer, size_t size)
{
  boost::asio::async_write(m_socket, boost::asio::buffer(buffer, size),
			   boost::bind(&BoostTcpAsyncClient::onWrite, this, buffer,
				       boost::asio::placeholders::bytes_transferred,
				       boost::asio::placeholders::error));
}


boost::asio::ip::tcp::socket&	BoostTcpAsyncClient::getSocket()
{
  return (m_socket);
}

void	BoostTcpAsyncClient::onRead(char* buffer, std::size_t size, std::size_t transferred, const boost::system::error_code& e)
{
  if (!e && size == transferred)
    notifyRead(buffer, transferred);
  else
    {
      notifyRead(buffer, 0);
      std::cout << "socket error read" << std::endl;
    }
}

void	BoostTcpAsyncClient::onWrite(char* buffer, std::size_t transferred,
				     const boost::system::error_code& e)
{
  if (!e)
    notifyWrite(buffer, transferred);
  else
    {
      std::cout << "boost socket write error" << std::endl;
    }
}

void	BoostTcpAsyncClient::close()
{
  m_socket.close();
}
