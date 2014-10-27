#ifndef BOOSTASYNCSERVER_HPP
#define BOOSTASYNCSERVER_HPP

#include "boost/asio.hpp"

namespace detail
{
  template<class AcceptorType>
  class BoostAsyncServer
  {
  private:
    AcceptorType	m_acceptor;

  public:
    BoostAsyncServer();
    ~BoostAsyncServer();

    void		accept();
    void		setTimeout(unsigned int second, unsigned int millisecond);
  };
};

typedef detail::BoostAsyncServer<boost::asio::ip::tcp::acceptor> TcpBoostAsyncServer;
typedef detail::BoostAsyncServer<boost::asio::ip::udp::acceptor> UdpBoostAsyncServer;

#include "BoostAsyncServer.tpp"

#endif /* BOOSTASYNCSERVER_HPP */
