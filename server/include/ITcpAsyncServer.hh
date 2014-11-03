#ifndef ITCPASYNCSERVER_HH
#define ITCPASYNCSERVER_HH

class ITcpAsyncServerListener;
class ITcpAsyncClient;

class ITcpAsyncServer
{
public:
  virtual ~ITcpAsyncServer() {};

  virtual void			addListener(ITcpAsyncServerListener* listener) = 0;
  virtual void			deleteListener(ITcpAsyncServerListener* listener) = 0;

  virtual void			accept() = 0;
  // virtual void			wait(unsigned int second, unsigned int millisecond) = 0;
  // virtual void			waitUntil(unsigned int second, unsigned int millisecond) = 0;

  virtual void			notifyAccept(ITcpAsyncClient* client) = 0;
  // virtual void			notifyTimeout() = 0;
};

#endif /* ITCPASYNCSERVER_HH */
