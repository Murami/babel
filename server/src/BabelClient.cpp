#include "BabelClient.hh"

BabelClient::BabelClient(ITcpAsyncClient& client, BabelServer& server) :
  m_client(client),
  m_server(server)
{
  /*
    - Initialiser le timeout (ping)
    - Lancer la boucle de read
  */
}

BabelClient::~BabelClient()
{
  /*
    - Deconnexion
    - Liberation des ressources
  */
}

void	BabelClient::onRead(ITcpAsyncClient& /*client*/, char* /*buffer*/, std::size_t /*size*/)
{
  /*
    - on refresh le buffer circulaire de lecture
    - on consomme les donnée valide
    - on appels les bonnes callback
    - on read
   */
}

void	BabelClient::onWrite(ITcpAsyncClient& /*client*/, char* /*buffer*/, std::size_t /*size*/)
{
  /*
    - on rotate le buffer simple d'ecriture de sorte a ce que les
      donnée non ecrite soit remise au debut
    - on read le buffer circulaire d'ecriture dans le buffer simple
    - on write le buffer simple sur le client
  */
}


void	BabelClient::onTimeout(IAsyncTimer& /*timer*/)
{
  /*
    - on ping
    - on verifie l'existence du serveur (check du dernier ping server)
    - on wait async
  */
}
