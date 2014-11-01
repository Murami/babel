#include "BoostAsyncService.hh"

BoostTcpAsyncClient()::BoostTcpAsyncClient(BoostAsyncService& service) : m_socket(service.getIOService())
{
}

void	BoostTcpAsyncClient::read()
{
}

void	BoostTcpAsyncClient::write()
{
}

boost::asio::ip::tcp::socket&	getSocket()
{
  return (m_socket);
}
