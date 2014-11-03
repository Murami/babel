#ifndef IASYNCTIMERLISTENER_HH
#define IASYNCTIMERLISTENER_HH

class IAsyncTimer;

class IAsyncTimerListener
{
public:
  virtual ~IAsyncTimerListener() {}

  virtual void	onTimeout(IAsyncTimer& timer) = 0;
};

#endif /* IASYNCTIMERLISTENER_HH */
