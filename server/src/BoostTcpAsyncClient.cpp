#include "BoostTcpAsyncClient.hh"
#include "BoostAsyncService.hh"

#include <boost/asio.hpp>

BoostTcpAsyncClient::BoostTcpAsyncClient(BoostAsyncService& service) : m_socket(service.getIOService())
{
}

void	BoostTcpAsyncClient::read(char* /*buffer*/, size_t /*size*/)
{
  // m_socket.async_read_some(boost::asio::buffer(buffer, size),
  // 			   boost::bind(
}

void	BoostTcpAsyncClient::write(char* /*buffer*/, size_t /*size*/)
{
}

boost::asio::ip::tcp::socket&	BoostTcpAsyncClient::getSocket()
{
  return (m_socket);
}

void	BoostTcpAsyncClient::onRead(char* /*buffer*/, std::size_t /*transferred*/, const boost::system::error_code& /*e*/)
{
}

void	BoostTcpAsyncClient::onWrite(char* /*buffer*/, std::size_t /*transferred*/, const boost::system::error_code& /*e*/)
{
}
