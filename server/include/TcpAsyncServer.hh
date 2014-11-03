#ifndef TCPASYNCSERVER_HH
#define TCPASYNCSERVER_HH

#include "ITcpAsyncServer.hh"

#include <list>

class TcpAsyncServer : public ITcpAsyncServer
{
private:
  typedef std::list<ITcpAsyncServerListener*> TcpAsyncServerListenerList;

  TcpAsyncServerListenerList	m_listenerList;

public:
  TcpAsyncServer(){}
  virtual ~TcpAsyncServer(){}

  void		addListener(ITcpAsyncServerListener* listener);
  void		deleteListener(ITcpAsyncServerListener* listener);

  void		notifyAccept(ITcpAsyncClient* client);
  // void		notifyTimeout();
};

#endif /* TCPASYNCSERVER_HH */
