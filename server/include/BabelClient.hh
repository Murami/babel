#ifndef BABELCLIENT_HH
#define BABELCLIENT_HH

#include "ITcpAsyncClientListener.hh"
#include "IAsyncTimerListener.hh"
#include "BoostAsyncTimer.hh"

#include <vector>
#include <cstdlib>

class ITcpAsyncClient;
class BabelServer;
class BoostAsyncService;
class BoostAsyncTimer;

class BabelClient : public ITcpAsyncClientListener, public IAsyncTimerListener
{
private:
  ITcpAsyncClient&	m_client;
  BabelServer&		m_server;
  BoostAsyncTimer	m_timer;
  std::vector<char>	m_writeBuffer;

public:
  BabelClient(ITcpAsyncClient& client, BabelServer& server, BoostAsyncService& service);
  ~BabelClient();

  void	onRead(ITcpAsyncClient& client, char* buffer, std::size_t size);
  void	onWrite(ITcpAsyncClient& client, char* buffer, std::size_t size);

  void	onTimeout(IAsyncTimer& timer);

private:
  // these are the callbacks called by the parsing in onRead
  // void	onLogin();
  // void	onLogout();
  // void	onRegister();
  // void	onCall();
  // void	onKOCall();
  // void	onOKCall();
  // void	onSendmsg();

  // these are answers to client
  // void	sendOKLogin();
  // void	sendKOLogin();
  // void	sendOKRegister();
  // void	sendKORegister();
  // void	sendOKCall();
  // void	sendKOCall();
  // void	sendUserinfo();
  // void	sendOKMsg();
  // void	sendKOMSg();
  // void	sendRecvMsg();
  // void	sendCall();
  void		sendPing();
};

#endif /* BABELCLIENT_HH */
