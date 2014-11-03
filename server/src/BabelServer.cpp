#include "BabelClient.hh"
#include "BabelServer.hh"
#include "BoostTcpAsyncServer.hh"

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

void		BabelServer::onAccept(ITcpAsyncServer& server, ITcpAsyncClient* client)
{
  BabelClient	*new_client;

  new_client = new BabelClient(*client, *this, m_service);
  m_clients.push_back(new_client);
  server.accept();

}

void	BabelServer::onTimeout(IAsyncTimer& /*server*/)
{
  /*
    - on ping tout les clients
    - on refait un wait async
  */
}
