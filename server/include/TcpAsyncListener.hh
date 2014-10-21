//
// TcpAsyncListener.hh for  in /home/anto/workspace/git/babel/server/include
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 18:25:52 2014 anto
// Last update Tue Oct 21 18:33:55 2014 anto
//

#ifndef TCPASYNCLISTENER_HH
#define TCPASYNCLISTENER_HH

class TcpAsyncAcceptor;
class TcpAsyncSession;

class TcpAsyncListener
{
public:
  virtual void onAccept(TcpAsyncAcceptor& acceptor, TcpAsyncSession* session, ErrorInfo& error) = 0;
  virtual void onRead(TcpAsyncSession& session, ErrorInfo& error) = 0;
  virtual void onWrite(TcpAsyncSession& session, ErrorInfo& error) = 0;
  virtual void onTimeout(TcpAsyncAcceptor& session, ErrorInfo& error) = 0;
};

#endif /* TCPASYNCLISTENER_HH */
