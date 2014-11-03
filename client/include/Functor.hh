#ifndef FUNCTOR_HH
#define FUNCTOR_HH

#include "IFunctor.hh"

class UserInfoFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class RecvMsgFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class CallFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class OkLoginFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class KoLoginFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class OkRegisterFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class KoRegisterFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class OkCallFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class KoCallFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class OkMsgFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class KoMsgFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class SampleFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class ImgFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

class PingFunctor : public IFunctor
{
public:
  void operator()(BabelCoreClient & core, void *data);
};

#endif
