#ifndef ITCPASYNCCLIENT_HH
#define ITCPASYNCCLIENT_HH

#include <cstdlib>

class ITcpAsyncClientListener;

class ITcpAsyncClient
{
public:
  virtual void			addListener(ITcpAsyncClientListener* listener) = 0;
  virtual void			deleteListener(ITcpAsyncClientListener* listener) = 0;

  virtual void			read(char* buffer, size_t size) = 0;
  virtual void			write(char* buffer, size_t size) = 0;

  virtual void			notifyRead() = 0;
};

#endif /* ITCPASYNCCLIENT_HH */
