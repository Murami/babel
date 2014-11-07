#include "BoostAsyncTimer.hh"
#include "BoostAsyncService.hh"

#include <boost/bind.hpp>

BoostAsyncTimer::BoostAsyncTimer(BoostAsyncService& service) :
  m_timer(service.getIOService())
{
}

BoostAsyncTimer::~BoostAsyncTimer()
{
}

void	BoostAsyncTimer::wait(unsigned int second, unsigned int microsecond)
{
  boost::posix_time::time_duration	duration;

  duration = (boost::posix_time::seconds(second) +
	      boost::posix_time::microseconds(microsecond));
  m_timer.expires_from_now(duration);
  m_timer.async_wait(boost::bind(&BoostAsyncTimer::onTimeout, this,
				 boost::asio::placeholders::error));
}

// void	BoostAsyncTimer::waitUntil(unsigned int second, unsigned int microsecond)
// {

// }

void	BoostAsyncTimer::onTimeout(const boost::system::error_code& /*e*/)
{
  notifyTimeout();
}
