#ifndef _IASYNC_SERVER_LISTENER_
# define _IASYNC_SERVER_LISTENER_

class	IAsyncServerListener
{
  class	TcpAsyncAcceptor;
  class TcpAsyncSession;

  virtual void		onAccept(TcpAsyncAcceptor& acceptor, TcpAsyncSession* session) = 0;
};

#endif /* _IASYNC_SERVER_LISTENER_ */
