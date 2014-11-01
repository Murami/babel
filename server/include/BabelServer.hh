#ifndef BABELSERVER_HH
#define BABELSERVER_HH

#include "ITcpAsyncServerListener.hh"

class BabelClient;

class BabelServer : public ITcpAsyncServerListener
{
private:
  ITcpAsyncServer&		m_server;
  // std::list<BabelAccountEntry>	m_accountList;
  std::list<BabelClient*>	m_sessionList;

public:
  BabelServer(ITcpAsyncServer& server);
  ~BabelServer();

  void	onAccept(ITcpAsyncServer& server, ITcpAsyncClient* client);
  void	onTimeout(ITcpAsyncServer& server);
};

#endif /* BABELSERVER_HH */
