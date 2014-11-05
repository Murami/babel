#include "BabelClient.hh"
#include "BabelServer.hh"
#include "BoostTcpAsyncServer.hh"
#include "BabelCall.hh"

BabelServer::BabelServer(ITcpAsyncServer& server, BoostAsyncService& service) :
  m_server(server), m_service(service)
{
  /*
    - on load les users
    - on init le timeout (ping)
  */
  m_server.addListener(this);
  m_server.accept();
}

BabelServer::~BabelServer()
{
  m_server.deleteListener(this);

  /*
    - on deconnect proprement tous les clients
    - on libere les ressources
  */
}

void				BabelServer::onAccept(ITcpAsyncServer& server,
						      ITcpAsyncClient* client)
{
  BabelClient*			new_client;

  new_client = new BabelClient(*client, *this, m_service);
  m_clients.push_back(new_client);
  server.accept();

}

void				BabelServer::onTimeout(IAsyncTimer& /*server*/)
{
  /*
    - on ping tout les clients
    - on refait un wait async
  */
}

BabelClient*			BabelServer::getClient(const std::string & name)
{
  for (std::list<BabelClient*>::iterator it = m_clients.begin();
       it != m_clients.end(); it++)
    {
      if ((*it)->getName() == name)
	return (*it);
    }
  return NULL;
}

bool				BabelServer::isAccount(const std::string & name)
{
  for (std::list<BabelAccountEntry>::iterator it = m_accountList.begin();
       it != m_accountList.end(); it++)
    {
      if ((*it).login == name)
	return true;
    }
  return false;
}

std::list<BabelClient*>		BabelServer::getAllClients()
{
  return (m_clients);
}

bool				BabelServer::registerClient(const std::string & name,
							    const std::string & mdp)
{
  BabelAccountEntry		entry;

  if (isAccount(name) == false)
    {
      entry.login = name;
      entry.md5pass = mdp;
      m_accountList.push_back(entry);
      return (true);
    }
  return (false);
}

bool				BabelServer::authClient(const std::string & name,
							const std::string & mdp)
{
  for (std::list<BabelAccountEntry>::iterator it = m_accountList.begin();
       it != m_accountList.end(); it++)
    {
      if ((*it).login == name && (*it).md5pass == mdp)
	return true;
    }
  return false;
}

bool				BabelServer::createCall(BabelClient* dest, BabelClient *src)
{
  for (std::list<BabelCall*>::iterator it = m_calls.begin();
       it != m_calls.end(); it++)
    {
      // if (dest == (*it)->getDestination() || dest == (*it)->getSource() ||
      // 	  src == (*it)->getDestination() || src == (*it)->getSource())
	return false;
    }
  m_calls.push_back(new BabelCall(dest, src));
  return true;
}
