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

  // m_acceptor.async_accept(client->getSocket(), boost::bind(&BoostTcpAsyncServer::onRead,
  // 							  this, client, boost::asio::placeholders::error));
  boost::bind(&BoostTcpAsyncServer::onRead, this, client, boost::asio::placeholders::error);
}

void	BoostTcpAsyncServer::wait(unsigned int /*second*/, unsigned int /*nanosecond*/)
{
  // m_timer.expires_from_now(boost::posix_time::second(second) + boost::posix_time::nanosecond(nanosecond));
  // m_timer.wait(boost::bind(&BoostAsyncService::onTimeout, this, boost::asio::placeholders::error));
}

void	BoostTcpAsyncServer::waitUntil(unsigned int /*second*/, unsigned int /*nanosecond*/)
{
  // m_timer.expires_at(boos::posix_time::second(second) + boos::posix_time::nanosecond(nanosecond));
  // m_timer.wait(boost::bind(&BoostAsyncService::onTimeout, this, boost::asio::placeholders::error));
}

void	BoostTcpAsyncServer::onRead(BoostTcpAsyncClient* /*client*/, boost::system::error_code& /*e*/)
{
  /* gerer les erreurs et nofifer les listener */
}

void	BoostTcpAsyncServer::onTimeout(boost::system::error_code& /*e*/)
{
  /* gerer les erreurs et notifier les litener */
}
