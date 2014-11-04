#ifndef BABELCLIENT_HH
#define BABELCLIENT_HH

#include "ITcpAsyncClientListener.hh"
#include "IAsyncTimerListener.hh"
#include "BoostAsyncTimer.hh"
#include "BabelProtocol.hh"

#include <vector>
#include <cstdlib>

class ITcpAsyncClient;
class BabelServer;
class BoostAsyncService;
class BoostAsyncTimer;

class BabelClient : public ITcpAsyncClientListener, public IAsyncTimerListener
{
  typedef void (BabelClient::*ptr)(void*);

private:
  Type			m_type;
  ITcpAsyncClient&	m_client;
  BabelServer&		m_server;
  BoostAsyncTimer	m_timer;
  char			m_readBuffer[4096];
  std::vector<char>	m_writeBuffer;
  std::map<Type, ptr>	m_map;

  bool			m_isConnect;
  std::string		m_name;
  std::string		m_mdp;

private:
  void	initMap();

public:
  BabelClient(ITcpAsyncClient& client, BabelServer& server, BoostAsyncService& service);
  ~BabelClient();


  const std::string &	getName() const;
  const std::string &	getMdp() const;
  bool			isConnect() const;

  void			onRead(ITcpAsyncClient& client, char* buffer, std::size_t size);
  void			onWrite(ITcpAsyncClient& client, char* buffer, std::size_t size);
  void			onTimeout(IAsyncTimer& timer);

private:
  // these are the callbacks called by the parsing in onRead
  void	onHeader(void *param);
  void	onLogin(void *param);
  void	onLogout(void *param);
  void	onRegister(void *param);
  void	onCall(void *param);
  void	onKOCall(void *param);
  void	onOKCall(void *param);
  void	onSendMsg(void *param);

  // these are answers to client
  void	sendOKLogin();
  void	sendKOLogin();
  void	sendOKRegister();
  void	sendKORegister();
  void	sendOKCall();
  void	sendKOCall();
  void	sendUserinfo();
  void	sendOKMsg();
  void	sendKOMSg();
  void	sendRecvMsg();
  void	sendCall();
  void	sendPing();
};

#endif /* BABELCLIENT_HH */
