#ifndef TCPASYNCCLIENT_HPP
#define TCPASYNCCLIENT_HPP

#include "ITcpAsyncClient.hh"

class ITcpAsyncClientListener;

class TcpAsyncClient : public ITcpAsyncClient
{
protected:
  CircularBuffer		m_inputBuffer;

private:
  std::list<AsyncListener*>	m_listenerList;

public:
  TcpAsyncClient();
  ~TcpAsyncClient();

  void		addListener(ITcpAsyncClientListener* listener);
  void		deleteListener(ITcpAsyncClientListener* listener);

  unsigned int	peekData(void* buffer, size_t size);
  unsigned int	readData(void* buffer, size_t size);
  unsigned int	writeData(void* buffer, size_t size);

  void		notifyRead();
};

#endif /* TCPASYNCCLIENT_HPP */
