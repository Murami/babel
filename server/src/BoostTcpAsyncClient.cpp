#include "BoostTcpAsyncClient.hh"
#include "BoostAsyncService.hh"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

BoostTcpAsyncClient::BoostTcpAsyncClient(BoostAsyncService& service) : m_socket(service.getIOService())
{
}

void	BoostTcpAsyncClient::readSome(char* buffer, size_t size)
{
  m_socket.async_read_some(boost::asio::buffer(buffer, size),
  			   boost::bind(&BoostTcpAsyncClient::onRead, this, buffer,
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
  std::cout << "BEGIN READ of size " << size << std::endl;
  boost::asio::async_read(m_socket, boost::asio::buffer(buffer, size),
			  boost::bind(&BoostTcpAsyncClient::onRead, this, buffer,
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

#include "BabelProtocol.hh"

void	BoostTcpAsyncClient::onRead(char* buffer, std::size_t transferred, const boost::system::error_code& /*e*/)
{
  notifyRead(buffer, transferred);
}

void	BoostTcpAsyncClient::onWrite(char* buffer, std::size_t transferred,
				     const boost::system::error_code& /*e*/)
{
  notifyWrite(buffer, transferred);
}
