#ifndef BABEL_HH
#define BABEL_HH

class BoostAsyncService;
class BoostTcpAsyncServer;

class Babel
{
private:
  BoostAsyncService*		m_service;
  BoostTcpAsyncServer*		m_server;

public:
  Babel();
  ~Babel();

  int	run();
};

#endif /* BABEL_HH */
