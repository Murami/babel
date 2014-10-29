#ifndef BOOSTTCPASYNCSERVER_HPP
#define BOOSTTCPASYNCSERVER_HPP

#include <boost/asio.hpp>
#incldue "TcpAsyncServer.hh"

class BoostTcpAsyncServer : public TcpAsyncServer
{
private:
  boost::asio::ip::tcp::acceptor	m_acceptor;
  boost::asio::deadline_timer		m_timer;

public:
  BoostTcpAsyncServer(BoostAsyncService& service, int port);
  virtual ~BoostTcpAsyncServer() {};

  void		accept();
  void		wait(unsigned int second, unsigned int millisecond);
  void		waitUntil(unsigned int second, unsigned int millisecond) = 0;
};

#endif /* BOOSTTCPASYNCSERVER_HPP */
