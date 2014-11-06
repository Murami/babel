#ifndef MUTEX_HH
#define MUTEX_HH

#include <QMutex>
#include "IMutex.hh"

class Mutex : public IMutex
{
public:
  Mutex();
  ~Mutex();

  void lock();
  bool tryLock();
  bool tryLock(int timeout);
  void unlock();

private:
  QMutex m_mutex;
};

#endif
