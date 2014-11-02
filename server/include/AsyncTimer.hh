#ifndef ASYNCTIMER_HH
#define ASYNCTIMER_HH

#include "IAsyncTimer.hh"

class AsyncTimer : public IAsyncTimer
{
  typedef std::list<IAsyncTimerListener> AsyncTimerListenerList;

private:
  AsyncTimerListenerList	m_listenerList;

public:
  AsyncTimer();
  virtual ~AsyncTimer();

  void	addListener(IAsyncTimerListener* listener);
  void	deleteListener(IAsynTimerListener* listener);

  void	notifyTimeout();
}

#endif /* ASYNCTIMER_HH */
