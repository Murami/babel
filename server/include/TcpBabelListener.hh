//
// TcpBabelListener.hh for  in /home/anto/workspace/git/babel/server/include
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 18:29:58 2014 anto
// Last update Tue Oct 21 18:38:46 2014 anto
//

#ifndef TCPBABELLISTENER_HH
#define TCPBABELLISTENER_HH

#include <list>
#include "BabelAccountEntry.hh"

class TcpAsynSession;
struct UserInfo;
struct LoginInfo;

class TcpBabelListener
{
private:
  std::list<BabelAccountEntry>	m_accountList;
  std::list<TcpAsynSession*>	m_sessionList;

public:
  void onAccept(TcpAsyncAcceptor& acceptor, TcpAsyncSession* session, ErrorInfo& error);
  void onRead(TcpAsyncSession& session, ErrorInfo& error);
  void onWrite(TcpAsyncSession& session, ErrorInfo& error);
  void onTimeout(TcpAsyncAcceptor& session, ErrorInfo& error);

private:
  void	onCall(TcpAsyncSession& session, CallInfo& info);
  void	onRegister(TcpAsynSession& session, LoginInfo& info);
  void	onLogin(TcpAsyncSession& session, LoginInfo& info);
  void	onLogout(TcpAsynSession& session);
  void	onHangout(TcpAsynSession& session);
  void	onSendMsg(TcpAsyncSession& session);
};

#endif /* TCPBABELLISTENER_HH */
