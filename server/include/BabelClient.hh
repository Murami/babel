#ifndef BABELCLIENT_HH
#define BABELCLIENT_HH

#include "ITcpAsyncClientListener.hh"
#include "IAsyncTimerListener.hh"

class ITcpAsyncClient;

class BabelClient : public ITcpAsyncClientListener, public IAsyncTimerListener
{
private:
  ITcpAsyncClient&	m_client;

public:
  BabelClient(ITcpAsyncClient& client);
  ~BabelClient();

  void	onRead(ITcpAsyncClient& client, char* buffer, std::size_t size);
  void	onWrite(ITcpAsyncClient& client, char* buffer, std::size_t size);

  void	onTimeout(IAsyncTimer& timer);
};

#endif /* BABELCLIENT_HH */
