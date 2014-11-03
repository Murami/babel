#include "Babel.hh"

Babel::Babel(int port) :
  m_server(m_service, port),
  m_babelServer(m_server, m_service)
{
}

Babel::~Babel()
{
}

int	Babel::run()
{
  m_service.run();
  return (0);
}
