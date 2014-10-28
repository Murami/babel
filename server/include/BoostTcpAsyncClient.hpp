#ifndef BOOSTTCPASYNCLIENT_HPP
#define BOOSTTCPASYNCLIENT_HPP

template<class UserData, unsigned int BufferSize = 1024>
class BoostTcpAsyncClient
{
private:
  boost::asio::ip::tcp	m_socket;

public:
  BoostTcpAsyncClient();
    ~BoostTcpAsyncClient();

  void	read();
  void	write();
};

#include "BoostTcpAsyncClient.tpp"

#endif /* BOOSTTCPASYNCLIENT_HPP */
