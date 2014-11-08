#ifndef IASYNCTIMER_HH
#define IASYNCTIMER_HH

class IAsyncTimerListener;

class IAsyncTimer
{
public:
  virtual ~IAsyncTimer() {}

  virtual void		setListener(IAsyncTimerListener* listener) = 0;
  virtual void		wait(unsigned int second, unsigned int microsecond) = 0;
  virtual unsigned int	getCurrentTime() const = 0;
};

#endif /* IASYNCTIMER_HH */
