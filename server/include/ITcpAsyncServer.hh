#ifndef ITCPASYNCSERVER_HH
#define IASYNCSERVER_HH

class IAsyncServerListener;

class ITpcAsyncServer
{
public:
  virtual void		addListener(IASyncServerListener* listener) = 0;
  virtual void		deleteListener(IAsyncServerListener* listener) = 0;

  virtual void		accept() = 0;
  virtual void		setTimeout(unsigned int second, unsigned int millisecond) = 0;

  virtual void		notifyAccept(ITcpAsyncClient* client) = 0;
  virtual void		notifyTimeout() = 0;

  virtual IAsyncService	getService() = 0;
};

#endif /* ITCPASYNCSERVER_HH */
