#ifndef I_MUTEX
#define I_MUTEX

class IMutex
{
public:
  virtual void lock() = 0;
  virtual bool tryLock() = 0;
  virtual bool tryLock(int timeout) = 0;
  virtual void unlock() = 0;
};

#endif
