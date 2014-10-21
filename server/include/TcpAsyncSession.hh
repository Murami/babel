//
// TcpAsyncSession.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 18:16:23 2014 anto
// Last update Tue Oct 21 18:23:33 2014 anto
//

#ifndef TCPASYNCSESSION_HH
#define TCPASYNCSESSION_HH

class TcpAsyncServer;

template<class UserData, unsined int BufferSize>
class TcpAsyncSession
{
public:
  UserData		userData;

protected:
  CircularBuffer	m_inputBuffer;
  CircularBuffer	m_ouputBuffer;
  TcpAsyncServer&	m_server;

public:
  TcpAsyncServer(TcpAsyncServer& server);
  ~TcpAsyncServer();

  void	addListener(TcpAsynListener& listener);
  void	deleteListener(TcpAsynListener& listener);

  void	peekData(void* buffer, size_t size);
  void	readData(void* buffer, size_t size);
  void	writeData(void* buffer, size_t size);

  virtual void	asyncRead();
  virtual void	asyncWrite();

protected:
  void	notifyWrite(ErrorInfo& error);
  void	notifyRead(ErrorInfo& error);
};

#endif /* TCPASYNCSESSION_HH */
