#ifndef BABEL_HH
#define BABEL_HH

class BoostAsyncService;
class BoostAsyncServer;

class Babel
{
private:
  BoostAsyncService*		m_service;
  BoostAsyncServer*		m_server;

public:
  Babel();
  ~Babel();

  int	run();
};

#endif /* BABEL_HH */
