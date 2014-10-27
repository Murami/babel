#ifndef BOOSTASYNCLIENT_HPP
#define BOOSTASYNCLIENT_HPP

namespace detail
{
  template<class UserData, unsigned int BufferSize = 1024, class SocketType>
  class BoostAsyncClient
  {
  private:
    SocketType	m_socket;

  public:
    BoostAsyncClient();
    ~BoostAsyncClient();

    void	read();
    void	write();
  };
};

typedef detail::BoostAsyncClient<boost::asio::ip::tcp::socket> TcpBoostAsyncClient;
typedef detail::BoostAsyncClient<boost::asio::ip::udp::socket> TcpBoostAsyncClient;

#include "BoostAsyncClient.tpp"

#endif /* BOOSTASYNCLIENT_HPP */
