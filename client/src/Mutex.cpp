#include "Mutex.hh"

Mutex::Mutex() {}

Mutex::~Mutex() {}

void Mutex::lock()
{
  m_mutex.lock();
}

bool Mutex::tryLock()
{
  return (m_mutex.tryLock());
}

bool Mutex::tryLock(int timeout)
{
  return (m_mutex.tryLock(timeout));
}

void Mutex::unlock()
{
  m_mutex.unlock();
}
