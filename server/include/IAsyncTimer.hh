#ifndef IASYNCTIMER_HH
#define IASYNCTIMER_HH

class IAsyncTimerListener;

class IAsyncTimer
{
public:
  virtual ~IAsyncTimer() {}

  virtual void	addListener(IAsyncTimerListener* listener) = 0;
  virtual void	deleteListener(IAsyncTimerListener* listener) = 0;

  virtual void	wait(unsigned int second, unsigned int microsecond) = 0;
  // virtual void	waitUntil(unsigned int second, unsigned int microsecond) = 0;
};

#endif /* IASYNCTIMER_HH */
