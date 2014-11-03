#include "BabelCall.hh"
#include "TcpAsyncSession.hh"

BabelCall(TcpAsyncSession* dest, TcpAsyncSession* src)
{
  m_destination = dest;
  m_source = src;
  m_timer = 0;
}

~BabelCall()
{

}

TcpAsyncSession*	getDestination()
{
  return (m_destination);
}

TcpAsyncSession*	getInterluctor(TcpAsyncSession* session)
{
  if (session == m_destination)
    return (m_source);
  else if (session == m_source)
    return (m_destination);
  else
    return (NULL);
}

TcpAsyncSession*	getSource()
{
  return (m_source);
}

unsigned int		getTimestart() const
{
  return (m_timer);
}
