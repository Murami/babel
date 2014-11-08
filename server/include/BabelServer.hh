#ifndef BABELSERVER_HH
#define BABELSERVER_HH

#include "ITcpAsyncServerListener.hh"
#include "IAsyncTimerListener.hh"
#include "BabelAccountEntry.hh"

#include <list>

class BabelClient;
class BabelCall;
class BoostAsyncService;

const std::string PATH_ACCOUNTS = "accounts.babel";

class BabelServer : public ITcpAsyncServerListener
{
private:
  ITcpAsyncServer&			m_server;
  BoostAsyncService&			m_service;
  std::list<BabelAccountEntry>		m_accountList;
  std::list<BabelClient*>		m_clients;
  std::list<BabelCall*>			m_calls;

public:
  BabelServer(ITcpAsyncServer& server, BoostAsyncService& service);
  ~BabelServer();



  BabelCall*			getCallFromDest(BabelClient * dest);
  bool				createCall(BabelClient* dest, BabelClient* src);
  void				popClient(BabelClient* client);
  void				popCall(BabelCall* client);
  void				loadAccounts();
  void				addAccount(BabelAccountEntry account);

  BabelClient*			getClient(const std::string & name);
  std::list<BabelClient*>	getAllClients();
  std::list<BabelAccountEntry>	getAllAccounts();

  bool				isAccount(const std::string & name);
  bool				registerClient(const std::string & name,
					       const std::string & mdp);
  bool				authClient(const std::string & name,
					   const std::string & mdp);

  void				onAccept(ITcpAsyncServer& server, ITcpAsyncClient* client);
};

#endif /* BABELSERVER_HH */
