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
  virtual void			readSome(char* buffer, size_t size) = 0;
  virtual void			writeSome(char* buffer, size_t size) = 0;
  // virtual void			wait(unsigned int second, unsigned int millisecond) = 0;
  // virtual void			waitUntil(unsigned int second, unsigned int millisecond) = 0;

  virtual void			notifyRead(char* buffer, std::size_t transferred) = 0;
  virtual void			notifyWrite(char* buffer, std::size_t transferred) = 0;

};

#endif /* ITCPASYNCCLIENT_HH */
