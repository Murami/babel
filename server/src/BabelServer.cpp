#include "BabelServer.hh"
#include "BoostTcpAsyncServer.hh"

BabelServer::BabelServer(ITcpAsyncServer& server) :
  m_server(server)
{
  /*
    - on load les users
    - on s'abonne au serveur
    - on init le timeout (ping)
    - on appele l'accept
  */
  m_server.addListener(this);
  m_server.accept();
}

BabelServer::~BabelServer()
{
  /*
    - on deconnect proprement tous les clients
    - on libere les ressources
    - on se desabonne du serveur
  */
}

void	BabelServer::onAccept(ITcpAsyncServer& /*server*/, ITcpAsyncClient* /*client*/)
{
  /*
    - on creer un BabelClient
    - on l'ajoute a la liste de client
  */
  std::cout << "ca accept" << std::endl;
}

void	BabelServer::onTimeout(IAsyncTimer& /*server*/)
{
  /*
    - on ping tout les clients
    - on refait un wait async
  */
}
