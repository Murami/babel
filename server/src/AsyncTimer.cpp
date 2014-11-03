#include "AsyncTimer.hh"

#include "IAsyncTimerListener.hh"

#include <algorithm>

AsyncTimer::AsyncTimer()
{
}

AsyncTimer::~AsyncTimer()
{
}

void	AsyncTimer::addListener(IAsyncTimerListener* listener)
{
  if (std::find(m_listenerList.begin(),
		m_listenerList.end(), listener) == m_listenerList.end())
    m_listenerList.push_back(listener);
}

void	AsyncTimer::deleteListener(IAsyncTimerListener* listener)
{
  m_listenerList.remove(listener);
}

void	AsyncTimer::notifyTimeout()
{
  AsyncTimerListenerList::iterator	it;

  for (it = m_listenerList.begin(); it != m_listenerList.end(); it++)
    (*it)->onTimeout(*this);
}
