#include "BoostTcpAsyncServer.hh"
#include "BoostTcpAsyncClient.hh"
#include "BoostAsyncService.hh"

#include <exception>
#include <stdexcept>
#include <boost/exception/all.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

BoostTcpAsyncServer::BoostTcpAsyncServer(BoostAsyncService& service, int port) try :
  m_io_service(service),
    m_acceptor(service.getIOService(),
	       boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_timer(service.getIOService())
{
}
catch (const boost::exception &e)
  {
    throw (std::runtime_error("Bind Error"));
  }

void	BoostTcpAsyncServer::accept()
{
  BoostTcpAsyncClient*	client = new BoostTcpAsyncClient(m_io_service);

  m_acceptor.async_accept(client->getSocket(), boost::bind(&BoostTcpAsyncServer::onAccept,
  							  this, client, boost::asio::placeholders::error));
}

void	BoostTcpAsyncServer::onAccept(BoostTcpAsyncClient* client, const boost::system::error_code& e)
{
  if (!e)
    notifyAccept(client);
}
