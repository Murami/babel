#ifndef BABELSERVER_HH
#define BABELSERVER_HH

#include "ITcpAsyncServerListener.hh"
#include "IAsyncTimerListener.hh"
#include "BabelAccountEntry.hh"

#include <list>

class BabelClient;
class BabelCall;
class BoostAsyncService;

class BabelServer : public ITcpAsyncServerListener, public IAsyncTimerListener
{
private:
  ITcpAsyncServer&		m_server;
  BoostAsyncService&		m_service;
  std::list<BabelAccountEntry>	m_accountList;
  std::list<BabelClient*>	m_clients;
  std::list<BabelCall*>		m_calls;

public:
  BabelServer(ITcpAsyncServer& server, BoostAsyncService& service);
  ~BabelServer();



  bool				createCall(BabelClient* dest, BabelClient* src);
  void				popClient(BabelClient* client);

  BabelClient*			getClient(const std::string & name);
  std::list<BabelClient*>	getAllClients();

  bool				isAccount(const std::string & name);
  bool				registerClient(const std::string & name,
					       const std::string & mdp);
  bool				authClient(const std::string & name,
					   const std::string & mdp);

  void				onAccept(ITcpAsyncServer& server, ITcpAsyncClient* client);
  void				onTimeout(IAsyncTimer& server);
};

#endif /* BABELSERVER_HH */
