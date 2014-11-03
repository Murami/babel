#include "BabelClient.hh"
#include "BoostAsyncTimer.hh"
#include "BoostAsyncService.hh"

BabelClient::BabelClient(ITcpAsyncClient& client, BabelServer& server, BoostAsyncService& service) :
  m_client(client),
  m_server(server),
  m_timer(service),
  m_readBuffer(4096),
  m_writeBuffer(4096)
{
  m_timer.addListener(this);
  m_timer.wait(5, 0);
  m_client.read(m_readBuffer, 4096);
}

BabelClient::~BabelClient()
{
  // m_timer.deleteListener(this);
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
  sendPing();
  m_timer.wait(5, 0);
  /*
    - on verifie l'existence du serveur (check du dernier ping server)
  */
}

void	BabelClient::sendPing()
{

}
