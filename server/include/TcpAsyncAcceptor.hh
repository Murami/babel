//
// TcpAsyncAcceptor.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 18:07:06 2014 anto
// Last update Tue Oct 21 18:13:13 2014 anto
//

#ifndef TCPASYNCACCEPTOR_HH
#define TCPASYNCACCEPTOR_HH

class TcpAsyncServer;

class TcpAsyncAcceptor
{
protected:
  TcpAsyncServer&	m_server;

public:
  TcpAsyncAcceptor(TcpAsyncServer& server);
  ~TcpAsyncAcceptor();

  void		addListener(TcpAsynListener& listener);
  void		deleteListener(TcpAsynListener& listener);

  virtual void	asyncAccept();
  virtual void	setTimeout(unsigned int second, unsigned int microsecond);

protected:
  void		notifyAccept(TcpAsyncSession& session, ErrorInfo& error);
  void		notifyTimeout(ErrorInfo& error);
};

#endif /* TCPASYNCACCEPTOR_HH */
