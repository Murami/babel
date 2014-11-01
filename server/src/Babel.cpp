#include "Babel.hh"

#include "BoostAsyncService.hh"
#include "BoostTcpAsyncServer.hh"

Babel::Babel()
{
  m_service = new BoostAsyncService();
  m_server = new BoostTcpAsyncServer(*m_service, 4242);
}

Babel::~Babel()
{
}

int	Babel::run()
{
  return (0);
}
