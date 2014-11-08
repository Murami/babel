#ifndef ASYNCTIMER_HH
#define ASYNCTIMER_HH

#include "IAsyncTimer.hh"

#include <list>

class AsyncTimer : public IAsyncTimer
{
private:
  IAsyncTimerListener*	m_listener;

public:
  AsyncTimer();
  virtual ~AsyncTimer();

  void	setListener(IAsyncTimerListener* listener);

  void	notifyTimeout(bool error);
};

#endif /* ASYNCTIMER_HH */
