#ifndef BOOSTASYNCTIMER_HH
#define BOOSTASYNCTIMER_HH

#include <boost/asio.hpp>
#include "AsyncTimer.hh"

class BoostAsyncService;

class BoostAsyncTimer : public AsyncTimer
{
private:
  boost::asio::deadline_timer	m_timer;

public:
  BoostAsyncTimer(BoostAsyncService& service);
  ~BoostAsyncTimer();

  void	cancel();
  void	wait(unsigned int second, unsigned int microsecond);
  void	onTimeout(const boost::system::error_code& e);
  unsigned int getCurrentTime() const;
};

#endif /* BOOSTASYNCTIMER_HH */
