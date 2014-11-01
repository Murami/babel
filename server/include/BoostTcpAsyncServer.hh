#ifndef BOOSTTCPASYNCSERVER_HPP
#define BOOSTTCPASYNCSERVER_HPP

#include <boost/asio.hpp>
#include "TcpAsyncServer.hh"

class BoostAsyncService;
class BoostTcpAsyncClient;

class BoostTcpAsyncServer : public TcpAsyncServer
{
private:
  BoostAsyncService&			m_io_service;
  boost::asio::ip::tcp::acceptor	m_acceptor;
  boost::asio::deadline_timer		m_timer;

public:
  BoostTcpAsyncServer(BoostAsyncService& service, int port);
  virtual ~BoostTcpAsyncServer() {};

  void		accept();
  void		wait(unsigned int second, unsigned int microsecond);
  void		waitUntil(unsigned int second, unsigned int microsecond);
  void		onRead(BoostTcpAsyncClient* client, const boost::system::error_code& e);
  void		onTimeout(const boost::system::error_code& e);
};

#endif /* BOOSTTCPASYNCSERVER_HPP */
