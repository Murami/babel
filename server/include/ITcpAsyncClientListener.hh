#ifndef ITCPASYNCCLIENTLISTENER_HH
#define ITCPASYNCCLIENTLISTENER_HH

#include <cstdlib>

class ITcpAsyncClient;

class ITcpAsyncClientListener
{
public:
  virtual void	onRead(ITcpAsyncClient& client, char* buffer, std::size_t transferred) = 0;
  virtual void	onWrite(ITcpAsyncClient& client, char* buffer, std::size_t transferred) = 0;
  virtual void	onTimeout(ITcpAsyncClient& client) = 0;
};

#endif /* ITCPASYNCCLIENTLISTENER_HH */
