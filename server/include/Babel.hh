#ifndef BABEL_HH
#define BABEL_HH

#include "BoostAsyncService.hh"
#include "BoostTcpAsyncServer.hh"
#include "BabelServer.hh"

class Babel
{
private:
  BoostAsyncService		m_service;
  BoostTcpAsyncServer		m_server;
  BabelServer			m_babelServer;

public:
  Babel(int port);
  ~Babel();

  int	run();
};

#endif /* BABEL_HH */
