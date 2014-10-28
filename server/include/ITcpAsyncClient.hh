#ifndef ITCPASYNCCLIENT_HH
#define ITCPASYNCCLIENT_HH

class ITcpAsyncClientListener;

class ITcpAsyncClient
{
public:
  virtual void		addListener(ITcpAsyncClientListener* listener) = 0;
  virtual void		deleteListener(ITcpAsyncClientListener* listener) = 0;

  virtual unsigned int	peekData(void* buffer, size_t size) = 0;
  virtual unsigned int	readData(void* buffer, size_t size) = 0;
  virtual unsigned int	writeData(void* buffer, size_t size) = 0;

  virtual void		read() = 0;
  virtual void		write() = 0;

  virtual void		notifyRead() = 0;

  virtual AsyncService&	getService() = 0;
};

#endif /* ITCPASYNCCLIENT_HH */
