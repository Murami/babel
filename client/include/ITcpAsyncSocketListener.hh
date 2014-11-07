#ifndef I_TCP_ASYNC_SOCKET_LISTENER
#define I_TCP_ASYNC_SOCKET_LISTENER

class ITcpAsyncSocketListener
{
public:
  virtual void onTcpConnect() = 0;
  virtual void onTcpDisconnect() = 0;
  virtual void onTcpError(int error) = 0;
  virtual void onTcpRead() = 0;
};

#endif
