#include "BabelClient.hh"
#include "BoostAsyncTimer.hh"
#include "BoostAsyncService.hh"
#include "ITcpAsyncClient.hh"
#include "BabelServer.hh"

BabelClient::BabelClient(ITcpAsyncClient& client, BabelServer& server,
			 BoostAsyncService& service) :
  m_client(client),
  m_server(server),
  m_timer(service)
{
  memset(m_writeBuffer, 0, 4096);
  memset(m_readBuffer, 0, 4096);
  m_isConnect = false;
  m_type = HEADER;
  m_timer.addListener(this);
  m_client.addListener(this);
  m_timer.wait(5, 0);
  m_client.read(m_readBuffer, sizeof(Header));
  m_isWriting = false;
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
  m_map[HEADER] = &BabelClient::onHeader;
  m_map[LOGIN] = &BabelClient::onLogin;
  m_map[LOGOUT] = &BabelClient::onLogout;
  m_map[REGISTER] = &BabelClient::onRegister;
  m_map[CALL] = &BabelClient::onCall;
  m_map[KO_CALL] = &BabelClient::onKOCall;
  m_map[OK_CALL] = &BabelClient::onOKCall;
  m_map[RECVMSG] = &BabelClient::onRecvMsg;

  m_headerType.push_back(HEADER);
  m_headerType.push_back(LOGOUT);
  m_headerType.push_back(PING);
  m_headerType.push_back(KO_LOGIN);
  m_headerType.push_back(OK_LOGIN);
  m_headerType.push_back(OK_REGISTER);
  m_headerType.push_back(KO_REGISTER);
  m_headerType.push_back(OK_MSG);
  m_headerType.push_back(KO_MSG);
  m_headerType.push_back(OK_CALL);
  m_headerType.push_back(KO_CALL);
}

void		BabelClient::onRead(ITcpAsyncClient& /*client*/, char* buffer,
			    std::size_t /* size */ )
{
  (this->*m_map[m_type])(static_cast<void*>(buffer));
}

void		BabelClient::onWrite(ITcpAsyncClient& /*client*/,
				     char* /*buffer*/, std::size_t /*size*/)
{
  Buffer       	buf;

  if (!m_queueWrite.empty()) // on utilise pas le buffer parametre
    {
      buf = m_queueWrite.front();
      m_queueWrite.pop();
      memcpy(m_writeBuffer, buf.data, buf.size);
      m_client.write(m_writeBuffer, buf.size);
    }
  else
    {
      m_isWriting = false;
    }
}

void		BabelClient::write(void* data, std::size_t size)
{
  Buffer	buffer;

  if (!m_isWriting)
    {
      memcpy(m_writeBuffer, data, size);
      m_client.write(m_writeBuffer, size);
      m_isWriting = true;
    }
  else
    {
      memcpy(buffer.data, data, size);
      buffer.size = size;
      m_queueWrite.push(buffer);
    }
}

void		BabelClient::onTimeout(IAsyncTimer& /*timer*/)
{
  sendPing();
  m_timer.wait(5, 0);
  /*
    - on verifie l'existence du serveur (check du dernier ping server)
  */
}

void		BabelClient::sendPing()
{

}

/* CALLBACKS DU ON READ */

void		BabelClient::onHeader(void *param)
{
  Header	*header = static_cast<Header*>(param);

  if (std::find(m_headerType.begin(),
		m_headerType.end(), header->type) == m_headerType.end())
    {
      m_type = header->type;
      m_client.read(m_readBuffer, header->size);
    }
  else
    {
      if (header->type != HEADER)
	(this->*m_map[m_type])(param);
      m_type = HEADER;
      m_client.read(m_readBuffer, sizeof(HEADER));
    }
}

void		BabelClient::onLogin(void *param)
{
  LoginInfo	*loginInfo = static_cast<LoginInfo*>(param);

  if (m_isConnect == false && m_server.authClient(std::string(loginInfo->user),
						  std::string(loginInfo->md5_pass)))
    {
      // notify other clients -> sendLogin
      // for () // comment je cible chaque client
      // 	{
      // 	  sendLogin(loginInfo);
      // 	}
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

void		BabelClient::onLogout(void * /*param*/)
{
  // notify server
  // fonction deconnect sur le servuer (pop de la list et le ( guerot ) fermeture de la socket)
  m_server.popClient(this);
  m_client.deleteListener(this);
  m_timer.deleteListener(this);
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

  if (m_server.createCall(m_server.getClient(std::string(call->user)), this))
    sendOKCall();
  else
    sendKOCall();
}

void		BabelClient::onKOCall(void * /*param*/)
{
  // destroycall(this);  -> getInterlocutor == -> pop
}

void		BabelClient::onOKCall(void * /*param */)
{
  // getcall()isValid -> true
}

void		BabelClient::onRecvMsg(void *param)
{
  Msg*		msg = static_cast<Msg*>(param);

  // verif size
  memcpy(msg->user, m_name.c_str(), m_name.length());
  msg->user[m_name.length() + 1] = 0;
  m_server.getClient(msg->user)->sendMsg(msg);
}

// ANSWSER TO CLIENT

void		BabelClient::sendOKLogin()
{
  Header	header;

  header.type = OK_LOGIN;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendKOLogin()
{
  Header	header;

  header.type = KO_LOGIN;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendOKRegister()
{
  Header	header;

  header.type = OK_REGISTER;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendKORegister()
{
  Header	header;

  header.type = KO_REGISTER;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendOKCall()
{
  Header	header;

  header.type = OK_CALL;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendKOCall()
{
  Header	header;

  header.type = KO_CALL;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendOKMsg()
{
  Header	header;

  header.type = OK_MSG;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendKOMSg()
{
  Header	header;

  header.type = KO_MSG;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendUserinfo()
{
  // recevoir user info en paramétre + header
  UserInfo	info;


  memcpy(info.user, &m_name[0], m_name.length());
  if (m_isConnect)
    info.status = CONNECTED;
  else
    info.status = DISCONNECTED;
  write(&info, sizeof(UserInfo));
}

void		BabelClient::sendMsg(Msg *msg)
{
  Header	header;

  header.type = SENDMSG;
  header.size = sizeof(Msg);
  write(&header, sizeof(Header));
  write(msg, sizeof(Msg));
}

void		BabelClient::sendCall()
{
  // init un CAll
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
