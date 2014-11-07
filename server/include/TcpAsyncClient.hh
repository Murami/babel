#ifndef TCPASYNCCLIENT_HH
#define TCPASYNCCLIENT_HH

#include "ITcpAsyncClient.hh"

#include <list>


class ITcpAsyncClientListener;

class TcpAsyncClient : public ITcpAsyncClient
{
  typedef std::list<ITcpAsyncClientListener*> TcpAsyncClientListenerList;

private:
  TcpAsyncClientListenerList	m_listenerList;

public:
  TcpAsyncClient();
  virtual ~TcpAsyncClient();

  void		addListener(ITcpAsyncClientListener* listener);
  void		deleteListener(ITcpAsyncClientListener* listener);

  void		notifyRead(char* buffer, std::size_t transferred);
  void		notifyWrite(char* buffer, std::size_t transferred);
};

#endif /* TCPASYNCCLIENT_HH */
