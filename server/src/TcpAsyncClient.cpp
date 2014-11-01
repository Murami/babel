#include "TcpAsyncClient.hh"

#include <algorithm>

TcpAsyncClient::TcpAsyncClient()
{
}

TcpAsyncClient::~TcpAsyncClient()
{
}

void	TcpAsyncClient::addListener(ITcpAsyncClientListener* listener)
{
  if (std::find(m_listenerList.begin(),
		m_listenerList.end(), listener) != m_listenerList.end())
    m_listenerList.push_back(listener);
}

void	TcpAsyncClient::deleteListener(ITcpAsyncClientListener* listener)
{
  m_listenerList.remove(listener);
}

void	TcpAsyncClient::notifyRead()
{
}
