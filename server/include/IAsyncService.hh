#ifndef IASYNCSERVICE_HH
#define IASYNCSERVICE_HH

class IAsyncService
{
public:
  virtual ~IAsyncService() {};

  virtual void	run() = 0;
};

#endif /* IASYNCSERVICE_HH */
