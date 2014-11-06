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
  initMap();
  memset(m_writeBuffer, 0, 4096);
  memset(m_readBuffer, 0, 4096);
  m_isConnect = false;
  m_isWriting = false;
  m_timer.addListener(this);
  m_client.addListener(this);
  m_timer.wait(5, 0);
  m_type = HEADER;
  m_client.read(m_readBuffer, sizeof(Header));
}

BabelClient::~BabelClient()
{
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
  m_map[SENDMSG] = &BabelClient::onRecvMsg;

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
			    std::size_t size)
{
  std::cout << "\033[35m[ server ]\tReading data from client\033[0m" << std::endl;
  if (size == 0)
    {
      std::cout << "\033[38m[ server ]\tClient disconnected\033[0m" << std::endl;
      onLogout(NULL);
      return;
    }
  (this->*m_map[m_type])(buffer);
}

void		BabelClient::onWrite(ITcpAsyncClient& /*client*/,
				     char* /*buffer*/, std::size_t /*size*/)
{
  Buffer       	buf;

  if (!m_queueWrite.empty())
    {
      std::cout << "\033[38m[ server ]\tFCUKING WARNING\033[0m" << std::endl;
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
  // Buffer	buffer;

  // if (!m_isWriting)
  //   {
      memset(m_writeBuffer, 0, 4096);
      memcpy(m_writeBuffer, data, size);
      m_client.write(m_writeBuffer, size);
  //     m_isWriting = true;
  //   }
  // else
  //   {
  //     memset(&buffer, 0, sizeof(Buffer));
  //     memcpy(buffer.data, data, size);
  //     buffer.size = size;
  //     m_queueWrite.push(buffer);
  //   }
}

void		BabelClient::onTimeout(IAsyncTimer& /*timer*/)
{
  sendPing();
  m_timer.wait(5, 0);
  /*
    - on verifie l'existence du serveur (check du dernier ping server)
  */
}

/* CALLBACKS DU ON READ */

void		BabelClient::onHeader(void *param)
{
  Header	*header = static_cast<Header*>(param);

  std::cout << "\033[36m[ server ]\tCallback Header\033[0m" << std::endl;
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
      m_client.read(m_readBuffer, sizeof(Header));
    }
}

void		BabelClient::onLogin(void *param)
{
  LoginInfo*			loginInfo = static_cast<LoginInfo*>(param);
  std::list<BabelAccountEntry>	accounts = m_server.getAllAccounts();
  std::list<BabelClient*>	clients = m_server.getAllClients();

  std::cout << "\033[36m[ server ]\tCallback Login\033[0m" << std::endl;
  if (m_isConnect == false && m_server.getClient(std::string(loginInfo->user)) == NULL &&
      m_server.authClient(std::string(loginInfo->user), std::string(loginInfo->md5_pass)))
    {
      m_name = std::string(loginInfo->user);
      m_mdp = std::string(loginInfo->md5_pass);
      m_isConnect = true;
      sendOKLogin();
      notifyConnexion(param);
    }
  else
    {
      m_isConnect = false;
      sendKOLogin();
    }
  m_type = HEADER;
  m_client.read(m_readBuffer, sizeof(Header));
}

void		BabelClient::onRegister(void *param)
{
  LoginInfo			*loginInfo = static_cast<LoginInfo*>(param);

  std::cout << "\033[36m[ server ]\tCallback Register\033[0m" << std::endl;
  if (m_isConnect == false && m_server.getClient(std::string(loginInfo->user)) == NULL &&
      m_server.registerClient(std::string(loginInfo->user),
			      std::string(loginInfo->md5_pass)))
    {
      m_name = std::string(loginInfo->user);
      m_mdp = std::string(loginInfo->md5_pass);
      m_isConnect = true;
      sendOKRegister();
      sendOKLogin();
      notifyConnexion(param);
    }
  else
    {
      m_isConnect = false;
      sendKORegister();
    }
  m_type = HEADER;
  m_client.read(m_readBuffer, sizeof(Header));
}

void		BabelClient::onCall(void *param)
{
  Call		*call = static_cast<Call*>(param);

  std::cout << "\033[36m[ server ]\tCallback CALL\033[0m" << std::endl;
  if (m_server.createCall(m_server.getClient(std::string(call->user)), this))
    sendOKCall();
  else
    sendKOCall();
  m_type = HEADER;
}

void		BabelClient::onRecvMsg(void *param)
{
  BabelClient*	tmp;
  Msg*		msg = static_cast<Msg*>(param);

  std::cout << "\033[36m[ server ]\tCallback RECV MSG\033[0m" << std::endl;
  if ((tmp = m_server.getClient(msg->user)) != NULL)
    {
      memcpy(msg->user, m_name.c_str(), m_name.length() + 1);
      tmp->sendMsg(msg);
      sendOKMsg();
    }
  else
    sendKOMSg();
  m_type = HEADER;
  m_client.read(m_readBuffer, sizeof(Header));
}

void		BabelClient::onLogout(void * /*param*/)
{
  LoginInfo			loginInfo;;

  std::cout << "\033[36m[ server ]\tCallback Logout\033[0m" << std::endl;
  // memcpy(loginInfo.user, m_name.c_str(), LOGIN_SIZE);
  // memcpy(loginInfo.md5_pass, m_mdp.c_str(), MD5_PASS_SIZE);
  // notifyConnexion(&loginInfo);
  m_server.popClient(this);
  m_client.deleteListener(this);
  m_timer.deleteListener(this);
  m_isConnect = false;
}

void		BabelClient::notifyConnexion(void *param)
{
  LoginInfo			*loginInfo = static_cast<LoginInfo*>(param);
  BabelAccountEntry		account;
  std::list<BabelAccountEntry>	accounts = m_server.getAllAccounts();
  std::list<BabelClient*>	clients = m_server.getAllClients();
  UserInfo			my_info;

  memset(my_info.user, 0, LOGIN_SIZE);
  memcpy(my_info.user, m_name.c_str(), m_name.length());
  my_info.status = CONNECTED;

  for (std::list<BabelAccountEntry>::iterator it = accounts.begin();
       it != accounts.end(); it++)
    {
      UserInfo	info;

      memset(info.user, 0, LOGIN_SIZE);
      strcpy(info.user, (*it).login.c_str());
      if (m_server.getClient((*it).login) != NULL && (*it).login != loginInfo->user)
	{
	  info.status = CONNECTED;
	  sendUserinfo(&info);
	}
      else if ((*it).login != loginInfo->user)
	{
	  info.status = DISCONNECTED;
	  sendUserinfo(&info);
	}
    }

  for (std::list<BabelClient*>::iterator it = clients.begin();
       it != clients.end(); it++)
    {
      if ((*it) != this)
	(*it)->sendUserinfo(&my_info);
    }
  account.login = m_name;
  account.md5pass = m_mdp;
  m_server.addAccount(account);
}

// ANSWSER TO CLIENT

void				BabelClient::sendUserinfo(UserInfo *info)
{
  Header			header;

  std::cout << "\033[31m[ server ]\tSEND USER INFO\033[0m" << std::endl;
  header.type = USERINFO;
  header.size = sizeof(UserInfo);
  write(&header, sizeof(Header));
  std::cout << "User Server [" << m_name << "]" << std::endl;
  std::cout << "write user info to client user";
  std::cout << "   [" << info->user << "]" << std::endl;
  write(info, sizeof(UserInfo));
}

void				BabelClient::sendPing()
{
  Header			header;

  std::cout << "\033[33m[ server ]\tPING\033[0m" << std::endl;
  header.type = PING;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void				BabelClient::sendMsg(Msg *msg)
{
  Header			header;

  std::cout << "\033[31m[ server ]\tSEND MSG\033[0m" << std::endl;
  header.type = RECVMSG;
  header.size = sizeof(Msg);
  write(&header, sizeof(Header));
  write(msg, sizeof(Msg));
}

void				BabelClient::sendCall()
{
  std::cout << "\033[31m[ server ]\tSEND CALL\033[0m" << std::endl;
}

// Gestion des données du client

const std::string&		BabelClient::getName() const
{
  return (m_name);
}

const std::string&		BabelClient::getMdp() const
{
  return (m_mdp);
}

bool				BabelClient::isConnect() const
{
  return (m_isConnect);
}

// SEND OK - KO

void				BabelClient::sendOKCall()
{
  Header	header;

  std::cout << "\033[31m[ server ]\tOK CALL\033[0m" << std::endl;
  header.type = OK_CALL;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void				BabelClient::sendKOCall()
{
  Header			header;

  std::cout << "\033[34m[ server ]\tKO CALL\033[0m" << std::endl;
  header.type = KO_CALL;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void				BabelClient::sendOKMsg()
{
  Header			header;

  std::cout << "\033[31m[ server ]\tOK MSG\033[0m" << std::endl;
  header.type = OK_MSG;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void				BabelClient::sendKOMSg()
{
  Header			header;

  std::cout << "\033[34m[ server ]\tKO MSG\033[0m" << std::endl;
  header.type = KO_MSG;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendOKRegister()
{
  Header	header;

  std::cout << "\033[31m[ server ]\tOK REGISTER\033[0m" << std::endl;
  header.type = OK_REGISTER;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendKORegister()
{
  Header	header;

  std::cout << "\033[34m[ server ]\tKO REGISTER\033[0m" << std::endl;
  header.type = KO_REGISTER;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::onKOCall(void * /*param*/)
{
  std::cout << "\033[36m[ server ]\tCallback KO CALL\033[0m" << std::endl;
  // destroycall(this);  -> getInterlocutor == -> pop
}

void		BabelClient::onOKCall(void * /*param */)
{
  std::cout << "\033[36m[ server ]\tCallback OK CALL\033[0m" << std::endl;
  // getcall()isValid -> true
}

void		BabelClient::sendOKLogin()
{
  Header	header;

  std::cout << "\033[31m[ server ]\tOK LOGIN\033[0m" << std::endl;
  header.type = OK_LOGIN;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}

void		BabelClient::sendKOLogin()
{
  Header	header;

  std::cout << "\033[34m[ server ]\tKO LOGIN\033[0m" << std::endl;
  header.type = KO_LOGIN;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}
