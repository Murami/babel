#ifndef ASYNCSERVER_HH
#define ASYNCSERVER_HH

class IAsyncService;

class AsyncServer
{
protected:
  IAsyncService&		m_service;

private:
  std::list<TcpAsyncListener*>	m_listenerList;

public:
  AsyncServer(IAsyncService& service);
  ~AsyncServer();

  virtual void	accept() = 0;
  virtual void	setTimeout(unsigned int second, unsigned int millisecond) = 0;

  void		addListener();
  void		deleteListener();

protected:
  void		notifyAccept(TcpAsyncSession& session);
  void		notifyTimeout();
};

#endif /* ASYNCSERVER_HH */
