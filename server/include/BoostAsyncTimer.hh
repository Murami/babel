#ifndef BOOSTASYNCTIMER_HH
#define BOOSTASYNCTIMER_HH

#include <boost/asio.hpp>
#include "AsyncTimer.hh"

class BoostAsyncService;

class BoostAsyncTimer : public AsyncTimer
{
public:
  BoostAsyncTimer(BoostAsyncService& service);
  ~BoostAsyncTimer();

  void	wait(unsigned int second, unsigned int microsecond);
  void	waitUntil(unsigned int second, unsigned int microsecond);

  void	onTimeout(const boost::system::error_code& e);

private:
  boost::asio::deadline_timer	m_timer;
};

#endif /* BOOSTASYNCTIMER_HH */
