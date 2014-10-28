#ifndef TCPBABELLISTENER_HH
#define TCPBABELLISTENER_HH

#include "AsyncServerListener.hh"
#include "AsyncClientListener.hh"

class TcpBabelListener : public AsyncServerListener, public AsyncClientListener
{
private:
  std::list<BabelAccountEntry>	m_accountList;
  std::list<TcpAsyncSession*>	m_sessionList;

public:
  TcpBabelListener();
  ~TcpBabelListener();

  void	onAccept(TcpAsyncServer& server, TcpAsyncClient* client);
  void	onRead(TcpAsyncClient* client);
  void	onTimeout(TcpAsyncServer* server);

private:
  // void	onHangUp(TcpAsyncClient& client);
  // void	onAnswer();
  void	onCall(TcpAsyncClient& client, LoginInfo& loginInfo);
  void	onLogin(TcpAsyncClient& client, UserInfos& userInfo);
  void	onLogout(TcpAsyncClient& client);
  void	onRegister(TcpAsyncClient& client, UserInfo& userInfo);
  boid	onSendmsg(TcpAsyncClient& client, MsgInfo& msgInfos);
};

#endif /* TCPBABELLISTENER_HH */
