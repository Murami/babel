#include <exception>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdexcept>
#include "BabelClient.hh"
#include "BabelServer.hh"
#include "BoostTcpAsyncServer.hh"
#include "BabelCall.hh"
#include "ITcpAsyncClient.hh"

BabelServer::BabelServer(ITcpAsyncServer& server, BoostAsyncService& service):
  m_server(server), m_service(service)
{
  m_server.addListener(this);
  m_server.accept();
  loadAccounts();
}

BabelServer::~BabelServer()
{
  m_server.deleteListener(this);
  /*
    - on deconnect proprement tous les clients
    - on libere les ressources
  */
}

void				BabelServer::loadAccounts()
{
  char*				name;
  char*				mdp;
  std::string			line;
  std::ifstream 		file(PATH_ACCOUNTS.c_str(), std::ios::in);

  try
    {
      if (file)
	{
	  while (getline(file, line))
	    {
	      BabelAccountEntry	account;
	      char			buffer[4096];

	      strcpy(buffer, line.c_str());
	      name = strtok(buffer, ";");
	      mdp = strtok(NULL, ";");
	      std::cout << "[name] = " << name << " [mdp] = " << mdp << std::endl;
	      account.login = std::string(name);
	      account.md5pass = std::string(mdp);
	      m_accountList.push_back(account);
	    }
	  file.close();
	}
    }
  catch (const std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
}

void				BabelServer::onAccept(ITcpAsyncServer& server,
						      ITcpAsyncClient* client)
{
  BabelClient*			new_client;

  new_client = new BabelClient(client, *this, m_service);
  m_clients.push_back(new_client);

  server.accept();
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

std::list<BabelAccountEntry>   	BabelServer::getAllAccounts()
{
  return (m_accountList);
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

void				BabelServer::addAccount(BabelAccountEntry account)
{
  std::ofstream file(PATH_ACCOUNTS.c_str(), std::ios::out | std::ios::app);

  if (file)
    {
      file << account.login << ";" << account.md5pass << "\n";
    }
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
      if (dest == (*it)->getDestination() || dest == (*it)->getSource() ||
      	  src == (*it)->getDestination() || src == (*it)->getSource())
	return false;
    }
  m_calls.push_back(new BabelCall(dest, src));
  return true;
}

BabelCall*			BabelServer::getCallFromDest(BabelClient* dest)
{
 for (std::list<BabelCall*>::iterator it = m_calls.begin();
       it != m_calls.end(); it++)
    {
      if (dest == (*it)->getDestination())
	return (*it);
    }
 return NULL;
}


void				BabelServer::popClient(BabelClient * client)
{
  m_clients.remove(client);
}

void				BabelServer::popCall(BabelCall * call)
{
  m_calls.remove(call);
}
