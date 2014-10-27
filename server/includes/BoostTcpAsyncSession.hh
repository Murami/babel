//
// BoostTcpAsyncSession.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 22:24:55 2014 anto
// Last update Tue Oct 21 22:32:32 2014 anto
//

#ifndef BOOSTTCPASYNCSESSION_HH
#define BOOSTTCPASYNCSESSION_HH

#include "TcpAsyncSession.hh"

template<class UserData, unsigned int BufferSize>
class BoostTcpAsyncSession : public TcpAsyncSession<UserData, BufferSize>
{
private:
  boost::asio::ip::tcp::socket	m_socket;

public:
  BoostTcpAsyncSession(BoostTcpAsyncServer& server);
  ~BoostTcpAsyncSession();

  void	asyncRead();
  void	asyncWrite();
};

#endif /* BOOSTTCPASYNCSESSION_HH */
