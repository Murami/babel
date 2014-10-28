#ifndef TCPASYNCSERVER_HH
#define TCPASYNCSERVER_HH

#include "ITcpAsyncServer.hh"

class ITcpAsyncClientListener;
class ITcpAsyncClient;

class TcpAsyncServer : public ITcpAsyncServer
{
private:
  std::list<ITcpAsyncServerListener*>	m_listenerList;

public:
  TcpAsyncServer(){}
  ~TcpAsyncServer(){}

  void		addListener(ITcpAsyncServerListener* listener);
  void		deleteListener(ITcpASyncServerListener* listener);

  void		notifyAccept(ITcpAsyncClient* client);
  void		notifyTimeout();
};

#endif /* TCPASYNCSERVER_HH */
