#ifndef ASYNCTIMER_HH
#define ASYNCTIMER_HH

#include "IAsyncTimer.hh"

#include <list>

class AsyncTimer : public IAsyncTimer
{
  typedef std::list<IAsyncTimerListener*> AsyncTimerListenerList;
  int	test;

private:
  AsyncTimerListenerList	m_listenerList;

public:
  AsyncTimer();
  virtual ~AsyncTimer();

  void	addListener(IAsyncTimerListener* listener);
  void	deleteListener(IAsyncTimerListener* listener);

  void	notifyTimeout();
};

#endif /* ASYNCTIMER_HH */
