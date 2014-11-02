#ifndef BOOSTASYNCTIMER_HH
#define BOOSTASYNCTIMER_HH

#include "AsyncTimer.hh"

class BoostAsyncTimer : public AsyncTimer
{
public:
  BoostAsyncTimer();
  ~BoostAsyncTimer();

  void	wait(unsigned int second, unsigned int microsecond);
  void	waitUntil(unsigned int second, unsigned int microsecond);

  void	onTimeout(const boost::system::error_code& e);
};

#endif /* BOOSTASYNCTIMER_HH */
