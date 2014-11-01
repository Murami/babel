#ifndef BABELCLIENT_HH
#define BABELCLIENT_HH

#include "ITcpAsyncClientListener.hh"

class ITcpAsyncClient;

class BabelClient : public ITcpAsyncClientListener
{
private:
  ITcpAsyncClient&	m_client;

public:
  BabelClient(ITcpAsyncClient& client);
  ~BabelClient();

  void	onRead(char* buffer, size_t size);
};

#endif /* BABELCLIENT_HH */
