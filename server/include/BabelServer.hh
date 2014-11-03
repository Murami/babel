#ifndef BABELSERVER_HH
#define BABELSERVER_HH

#include "ITcpAsyncServerListener.hh"
#include "IAsyncTimerListener.hh"

#include <list>

class BabelClient;
class BoostAsyncService;

class BabelServer : public ITcpAsyncServerListener, public IAsyncTimerListener
{
private:
  ITcpAsyncServer&		m_server;
  BoostAsyncService&		m_service;
  // std::list<BabelAccountEntry>	m_accountList;
  std::list<BabelClient*>	m_clients;

public:
  BabelServer(ITcpAsyncServer& server, BoostAsyncService& service);
  ~BabelServer();

  void	onAccept(ITcpAsyncServer& server, ITcpAsyncClient* client);
  void	onTimeout(IAsyncTimer& server);
};

#endif /* BABELSERVER_HH */
