#include "BabelCall.hh"
#include "BabelClient.hh"

BabelCall::BabelCall(BabelClient* dest, BabelClient* src)
{
  m_destination = dest;
  m_source = src;
  m_timer = 0;
}

~BabelCall::BabelCall()
{

}

BabelClient*		BabelCall::getDestination()
{
  return (m_destination);
}

BabelClient*		BabelCall::getInterluctor(BabelClient* session)
{
  if (session == m_destination)
    return (m_source);
  else if (session == m_source)
    return (m_destination);
  else
    return (NULL);
}

BabelClient*		BabelCall::getSource()
{
  return (m_source);
}

unsigned int		BabelCall::getTimestart() const
{
  return (m_timer);
}

bool			BabelCall::isValid() const
{
  return (m_isValid);
}

void			BabelCall::setValid(bool b)
{
  m_isValid = b;
}
