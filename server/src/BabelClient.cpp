#include "BabelClient.hh"
#include "BoostAsyncTimer.hh"
#include "BoostAsyncService.hh"
#include "ITcpAsyncClient.hh"
#include "BabelServer.hh"

BabelClient::BabelClient(ITcpAsyncClient& client, BabelServer& server, BoostAsyncService& service) :
  m_client(client),
  m_server(server),
  m_timer(service),
  m_writeBuffer(4096)
{
  m_isConnect = false;
  m_type = HEADER;
  m_timer.addListener(this);
  m_timer.wait(5, 0);
  m_client.read(m_readBuffer, sizeof(Header));
}

BabelClient::~BabelClient()
{
  // m_timer.deleteListener(this);
  /*
    - Deconnexion
    - Liberation des ressources
  */
}

void	BabelClient::initMap()
{
  m_map[LOGIN] = &BabelClient::onLogin;
  m_map[LOGOUT] = &BabelClient::onLogout;
  m_map[REGISTER] = &BabelClient::onRegister;
  m_map[CALL] = &BabelClient::onCall;
  m_map[KO_CALL] = &BabelClient::onKOCall;
  m_map[OK_CALL] = &BabelClient::onOKCall;
  m_map[SENDMSG] = &BabelClient::onSendMsg;
}

void	BabelClient::onRead(ITcpAsyncClient& /*client*/, char* buffer, std::size_t /* size */ )
{
  (this->*m_map[m_type])(static_cast<void*>(buffer));
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

/* CALLBACKS DU ON READ */

void		BabelClient::onHeader(void *param)
{
  Header	*header = static_cast<Header*>(param);

  m_type = header->type;
  m_client.read(m_readBuffer, header->size);
}

void		BabelClient::onLogin(void *param)
{
  LoginInfo	*loginInfo = static_cast<LoginInfo*>(param);

  if (m_isConnect == false && m_server.authClient(std::string(loginInfo->user),
						  std::string(loginInfo->md5_pass)))
    {
      // notify other clients
      m_name = std::string(loginInfo->user);
      m_mdp = std::string(loginInfo->md5_pass);
      m_isConnect = true;
      sendOKLogin();
    }
  else
    {
      m_isConnect = false;
      sendKOLogin();
    }
  m_client.read(m_readBuffer, sizeof(Header));
}

void		BabelClient::onLogout(void *param)
{
  // notify server
  m_isConnect = false;
}

void		BabelClient::onRegister(void *param)
{
  LoginInfo	*loginInfo = static_cast<LoginInfo*>(param);

  if (m_isConnect == false && m_server.registerClient(std::string(loginInfo->user),
						      std::string(loginInfo->md5_pass)))
    {
      m_name = std::string(loginInfo->user);
      m_mdp = std::string(loginInfo->md5_pass);
      m_isConnect = true;
      sendOKRegister();
      sendOKLogin();
    }
  else
    {
      m_isConnect = false;
      sendKORegister();
    }
}

void		BabelClient::onCall(void *param)
{
  Call		*call = static_cast<Call*>(param);

  if (true)
    {
      sendOKCall();
    }
  else
    {
      sendKOCall();
    }
}

void		BabelClient::onKOCall(void *param)
{
  if (true)
    {

    }
  else
    {

    }
}

void		BabelClient::onOKCall(void *param)
{
  if (true)
    {

    }
  else
    {

    }
}

void		BabelClient::onSendMsg(void *param)
{
  if (true)
    {
      sendOKMsg();
    }
  else
    {
      sendKOMSg();
    }
}

// ANSWSER TO CLIENT

void		BabelClient::sendOKLogin()
{

}

void		BabelClient::sendKOLogin()
{

}

void		BabelClient::sendOKRegister()
{

}

void		BabelClient::sendKORegister()
{

}

void		BabelClient::sendOKCall()
{

}

void		BabelClient::sendKOCall()
{

}

void		BabelClient::sendUserinfo()
{

}

void		BabelClient::sendOKMsg()
{

}

void		BabelClient::sendKOMSg()
{

}

void		BabelClient::sendRecvMsg()
{

}

void		BabelClient::sendCall()
{

}


// Gestion des données du client

const std::string&	BabelClient::getName() const
{
  return (m_name);
}

const std::string&	BabelClient::getMdp() const
{
  return (m_mdp);
}

bool			BabelClient::isConnect() const
{
  return (m_isConnect);
}
