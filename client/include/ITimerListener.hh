#ifndef I_TIMER_LISTENER
#define I_TIMER_LISTENER

class ITimerListener
{
public:
  virtual void onTimeout(int id) = 0;
};

#endif
