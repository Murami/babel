#ifndef I_UDP_ASYNC_SOCKET_LISTENER
#define I_UDP_ASYNC_SOCKET_LISTENER

class IUdpAsyncSocketListener
{
public:
  virtual void onError(int error) = 0;
  virtual void onRead() = 0;
};

#endif
