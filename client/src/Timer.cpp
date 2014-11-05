#include "Timer.hh"
#include "ITimerListener.hh"

int Timer::global_timer_id = 0;

Timer::Timer()
{
  m_id = global_timer_id;
  global_timer_id++;
  connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

Timer::~Timer() {}

int	Timer::interval() const
{
  return (m_timer.interval());
}

bool	Timer::isActive() const
{
  return (m_timer.isActive());
}

void	Timer::setInterval(int msec)
{
  m_timer.setInterval(msec);
}

void	Timer::start(int msec)
{
  m_timer.start(msec);
}

void	Timer::start()
{
  m_timer.start();
}

void	Timer::stop()
{
  m_timer.stop();
}

int	Timer::getTimerId()
{
  return (m_id);
}

void Timer::onTimeout()
{
  std::list<ITimerListener *>::iterator it;

  it = listenerList.begin();
  for (; it != listenerList.end(); ++it)
    (*it)->onTimeout(m_id);
}

void Timer::addListener(ITimerListener * listener)
{
  listenerList.push_front(listener);
}
