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

void		BoostAsyncTimer::wait(unsigned int second, unsigned int microsecond)
{
  boost::posix_time::time_duration	duration;

  duration = (boost::posix_time::seconds(second) +
	      boost::posix_time::microseconds(microsecond));
  m_timer.expires_from_now(duration);
  m_timer.async_wait(boost::bind(&BoostAsyncTimer::onTimeout, this,
				 boost::asio::placeholders::error));
}

void		BoostAsyncTimer::cancel()
{
  m_timer.cancel();
}

void		BoostAsyncTimer::onTimeout(const boost::system::error_code& e)
{
  if (e == boost::asio::error::operation_aborted)
    notifyTimeout(false);
  else if (!e)
    notifyTimeout(true);
}

unsigned int	BoostAsyncTimer::getCurrentTime() const
{
  boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::ptime epoch = boost::posix_time::ptime(boost::gregorian::date(1970, 1, 1));
  return (static_cast<unsigned int>((time - epoch).total_milliseconds()));
}
