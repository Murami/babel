#ifndef BABELSERVER_HH
#define BABELSERVER_HH

#include "ITcpAsyncServerListener.hh"
#include "IAsyncTimerListener.hh"

class BabelClient;

class BabelServer : public ITcpAsyncServerListener, public IAsyncTimerListener
{
private:
  ITcpAsyncServer&		m_server;
  // std::list<BabelAccountEntry>	m_accountList;
  std::list<BabelClient*>	m_sessionList;

public:
  BabelServer(ITcpAsyncServer& server);
  ~BabelServer();

  void	onAccept(ITcpAsyncServer& server, ITcpAsyncClient* client);
  void	onTimeout(IAsyncTimer& server);
};

#endif /* BABELSERVER_HH */
