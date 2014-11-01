#include "BoostTcpAsyncClient.hh"
#include "BoostAsyncService.hh"

BoostTcpAsyncClient::BoostTcpAsyncClient(BoostAsyncService& service) : m_socket(service.getIOService())
{
}

void	BoostTcpAsyncClient::read(char* /*buffer*/, size_t /*size*/)
{
}

void	BoostTcpAsyncClient::write(char* /*buffer*/, size_t /*size*/)
{
}

boost::asio::ip::tcp::socket&	BoostTcpAsyncClient::getSocket()
{
  return (m_socket);
}
