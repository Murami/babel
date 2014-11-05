#include "BoostAsyncTimer.hh"
#include "BoostAsyncService.hh"

BoostAsyncTimer::BoostAsyncTimer(BoostAsyncService& service) : m_timer(service.getIOService())
{
}

BoostAsyncTimer::~BoostAsyncTimer()
{
}

void	BoostAsyncTimer::wait(unsigned int /*second*/, unsigned int/* microsecond*/)
{
}

void	BoostAsyncTimer::waitUntil(unsigned int /*second*/, unsigned int /*microsecond*/)
{
}
