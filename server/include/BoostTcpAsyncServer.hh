#ifndef BOOSTTCPASYNCSERVER_HPP
#define BOOSTTCPASYNCSERVER_HPP

#include <boost/asio.hpp>
#incldue "TcpAsyncServer.hh"

class BoostTcpAsyncServer : public TcpAsyncServer
{
private:
  boost::asio::ip::tcp::acceptor	m_acceptor;

public:
  BoostTcpAsyncServer(BoostAsyncService& service);
  virtual ~BoostTcpAsyncServer();

  void		accept();
  void		setTimeout(unsigned int second, unsigned int millisecond);
};

#endif /* BOOSTTCPASYNCSERVER_HPP */
