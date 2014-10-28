#ifndef ITCPASYNCCLIENTLISTENER_HH
#define ITCPASYNCCLIENTLISTENER_HH

class ITcpAsyncClient;

class ITcpAsyncClientListener
{
public:
  virtual void	onRead(ITcpAsyncClient& client) = 0;
  virtual void	onTimeout(ITcpAsyncClient& client) = 0;
};

#endif /* ITCPASYNCCLIENTLISTENER_HH */
