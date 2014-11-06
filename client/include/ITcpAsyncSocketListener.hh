#ifndef I_TCP_ASYNC_SOCKET_LISTENER
#define I_TCP_ASYNC_SOCKET_LISTENER

class ITcpAsyncSocketListener
{
public:
  virtual void onConnect() = 0;
  virtual void onDisconnect() = 0;
  virtual void onError(int error) = 0;
  virtual void onRead() = 0;
};

#endif
