#include "TcpAsyncServer.hh"

#include "ITcpAsyncServerListener.hh"

#include <algorithm>

void	TcpAsyncServer::addListener(ITcpAsyncServerListener* listener)
{
  if (std::find(m_listenerList.begin(),
		m_listenerList.end(), listener) == m_listenerList.end())
    m_listenerList.push_back(listener);
}

void	TcpAsyncServer::deleteListener(ITcpAsyncServerListener* listener)
{
  m_listenerList.remove(listener);
}

void	TcpAsyncServer::notifyAccept(ITcpAsyncClient* client)
{
  TcpAsyncServerListenerList::iterator	it;

  for (it = m_listenerList.begin(); it != m_listenerList.end(); it++)
    (*it)->onAccept(*this, client);
}
