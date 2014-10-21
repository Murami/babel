//
// BoostTcpAsyncAcceptor.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 22:33:22 2014 anto
// Last update Tue Oct 21 22:35:54 2014 anto
//

#ifndef BOOSTTCPASYNCACCEPTOR_HH
#define BOOSTTCPASYNCACCEPTOR_HH

class BoostTcpAsyncAcceptor : public TcpAsyncAcceptor
{
private:
  boost::asio::io::tcp::acceptor	m_acceptor;

public:
  BoostTcpAsyncAcceptor(BoostTcpAsyncServer& server);
  ~BoostTcpAsyncAcceptor();

  void	asyncAccept();
  void	setTimeout(unsigned int second, unsigned int microsecond);
};

#endif /* BOOSTTCPASYNCACCEPTOR_HH */
