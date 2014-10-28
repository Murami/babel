#ifndef ITCPASYNCSERVERLISTENER_HH
#define ITCPASYNCSERVERLISTENER_HH

class ITcpAsyncServer;
class ITcpAsyncClient;

class ITcpAsyncServerListener
{
public:
  virtual void	onAccept(ITcpAsyncServer& server, ITcpAsyncClient* client) = 0;
};

#endif /* ITCPASYNCSERVERLISTENER_HH */
