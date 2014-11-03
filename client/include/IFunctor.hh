#ifndef I_FUNCTOR_HH
#define I_FUNCTOR_HH

class BabelCoreClient;

class IFunctor
{
public:
  virtual void operator()(BabelCoreClient & core, void *data) = 0;
};

#endif
