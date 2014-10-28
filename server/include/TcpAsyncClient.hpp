#ifndef TCPASYNCCLIENT_HPP
#define TCPASYNCCLIENT_HPP

#include "ITcpAsyncClient.hh"

class ITcpAsyncClientListener;

template<class UserData, unsigned int BufferSize>
class TcpAsyncClient : public ITcpAsyncClient
{
public:
  UserData			userdata;

protected:
  CircularBuffer<BufferSize>	m_inputBuffer;
  CircularBuffer<BufferSize>	m_outputBuffer;

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

#include "TcpAsyncClient.hpp"

#endif /* TCPASYNCCLIENT_HPP */
