#include "BoostTcpAsyncServer.hh"
#include "BoostTcpAsyncClient.hh"
#include "BoostAsyncService.hh"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

BoostTcpAsyncServer::BoostTcpAsyncServer(BoostAsyncService& service, int port) :
  m_io_service(service),
  m_acceptor(service.getIOService(), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
  m_timer(service.getIOService())
{
}

void	BoostTcpAsyncServer::accept()
{
  BoostTcpAsyncClient*	client = new BoostTcpAsyncClient(m_io_service);

  m_acceptor.async_accept(client->getSocket(), boost::bind(&BoostTcpAsyncServer::onRead,
  							  this, client, boost::asio::placeholders::error));
}

void	BoostTcpAsyncServer::wait(unsigned int second, unsigned int microsecond)
{
  m_timer.expires_from_now(boost::posix_time::seconds(second) + boost::posix_time::microseconds(microsecond));
  m_timer.async_wait(boost::bind(&BoostTcpAsyncServer::onTimeout, this, boost::asio::placeholders::error));
}

void	BoostTcpAsyncServer::waitUntil(unsigned int second, unsigned int microsecond)
{
  boost::posix_time::ptime	expiration(boost::gregorian::date(1970,1,1),
					   boost::posix_time::seconds(second) +
					   boost::posix_time::microseconds(microsecond));
  m_timer.expires_at(expiration);
  m_timer.async_wait(boost::bind(&BoostTcpAsyncServer::onTimeout, this, boost::asio::placeholders::error));
}

void	BoostTcpAsyncServer::onRead(BoostTcpAsyncClient* /*client*/, const boost::system::error_code& /*e*/)
{
  /* gerer les erreurs et nofifer les listener */
}

void	BoostTcpAsyncServer::onTimeout(const boost::system::error_code& /*e*/)
{
  /* gerer les erreurs et notifier les litener */
}
