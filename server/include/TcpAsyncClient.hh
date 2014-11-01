#ifndef TCPASYNCCLIENT_HH
#define TCPASYNCCLIENT_HH

#include "ITcpAsyncClient.hh"

#include <list>


class ITcpAsyncClientListener;

class TcpAsyncClient : public ITcpAsyncClient
{
private:
  std::list<ITcpAsyncClientListener*>	m_listenerList;

public:
  TcpAsyncClient();
  ~TcpAsyncClient();

  void		addListener(ITcpAsyncClientListener* listener);
  void		deleteListener(ITcpAsyncClientListener* listener);

  void		notifyRead();
};

#endif /* TCPASYNCCLIENT_HH */
