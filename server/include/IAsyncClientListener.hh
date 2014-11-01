#ifndef _IASYNC_CLIENT_LISTENER_
# define _IASYNC_CLIENT_LISTENER_

class IAsyncClientListener
{
  class TcpAsyncSession;

public:
  virtual void	onRead(TcpAsyncSession& session) = 0;
  virtual void	onTimeout(TcpAsyncSession& session) = 0;
  virtual void	onWrite(TcpAsyncSession& session) = 0;
};

#endif /* _IASYNC_CLIENT_LISTENER_ */
