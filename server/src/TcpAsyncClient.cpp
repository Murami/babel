#include <iostream>

#include "TcpAsyncClient.hh"

#include "ITcpAsyncClientListener.hh"

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
  		m_listenerList.end(), listener) == m_listenerList.end())
    m_listenerList.push_back(listener);
}

void	TcpAsyncClient::deleteListener(ITcpAsyncClientListener* listener)
{
  m_listenerList.remove(listener);
}

void	TcpAsyncClient::notifyRead(char* buffer, std::size_t transferred)
{
  TcpAsyncClientListenerList::iterator	it;
  std::cout << m_listenerList.size() << std::endl;
  for (it = m_listenerList.begin(); it != m_listenerList.end(); it++)
    {
      (*it)->onRead(*this, buffer, transferred);
    }
}

void	TcpAsyncClient::notifyWrite(char* buffer, std::size_t transferred)
{
  TcpAsyncClientListenerList::iterator	it;

  for (it = m_listenerList.begin(); it != m_listenerList.end(); it++)
    (*it)->onWrite(*this, buffer, transferred);
}
