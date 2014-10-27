#ifndef ASYNCCLIENT_HPP
#define ASYNCCLIENT_HPP

class IAsyncService;

template<class UserData, unsigned int BufferSize>
class AsyncClient
{
public:
  UserData	userdata;

protected:
  CircularBuffer<BufferSize>	m_inputBuffer;
  CircularBuffer<BufferSize>	m_outputBuffer;
  AsyncServer&			m_server;

private:
  std::list<AsyncListener*>	m_listenerList;

public:
  AsyncClient(IAsyncService& service);
  ~AsyncClient();

  void	addListener(AsyncListener& listener);
  void	deleteListener(AsyncListener& listener);

  unsigned int	peekData(void* buffer, size_t size);
  unsigned int	readData(void* buffer, size_t size);
  unsigned int	writeData(void* buffer, size_t size);

  virtual void	read() = 0;
  virtual void	write() = 0;

private:
  void	notifyRead();
};

#include "AsyncClient.hpp"

#endif /* ASYNCCLIENT_HPP */
