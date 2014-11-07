#ifndef BOOSTTCPASYNCLIENT_HH
#define BOOSTTCPASYNCLIENT_HH

#include "TcpAsyncClient.hh"

#include <boost/asio.hpp>

class BoostAsyncService;

class BoostTcpAsyncClient : public TcpAsyncClient
{
private:
  boost::asio::ip::tcp::socket	m_socket;

public:
  BoostTcpAsyncClient(BoostAsyncService& service);
  ~BoostTcpAsyncClient();

  void				read(char* buffer, size_t size);
  void				write(char* buffer, size_t size);
  void				readSome(char* buffer, size_t size);
  void				writeSome(char* buffer, size_t size);

  boost::asio::ip::tcp::socket&	getSocket();

  void				onRead(char* buffer, std::size_t size,
				       std::size_t transferred,
				       const boost::system::error_code& e);
  void				onWrite(char* buffer, std::size_t transferred,
					const boost::system::error_code& e);
};

#endif /* BOOSTTCPASYNCLIENT_HH */
