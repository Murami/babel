#include "AsyncTimer.hh"

#include "IAsyncTimerListener.hh"

#include <algorithm>

AsyncTimer::AsyncTimer()
{

}

AsyncTimer::~AsyncTimer()
{
}

void	AsyncTimer::setListener(IAsyncTimerListener* listener)
{
  m_listener = listener;
}

void	AsyncTimer::notifyTimeout(bool error)
{
  m_listener->onTimeout(*this, error);
}
