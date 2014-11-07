#ifndef I_UDP_ASYNC_SOCKET_LISTENER
#define I_UDP_ASYNC_SOCKET_LISTENER

class IUdpAsyncSocketListener
{
public:
  virtual void onUdpError(int error) = 0;
  virtual void onUdpRead() = 0;
};

#endif
