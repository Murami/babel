#include "BabelClient.hh"
#include "BoostAsyncTimer.hh"
#include "BoostAsyncService.hh"
#include "BoostTcpAsyncClient.hh"
#include "ITcpAsyncClient.hh"
#include "BabelServer.hh"

BabelClient::BabelClient(BoostTcpAsyncClient* client, BabelServer& server,
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
  m_timer.setListener(this);
  m_client->addListener(this);
  m_timer.wait(1, 0);
  m_type = HEADER;
  m_client->read(m_readBuffer, sizeof(Header));
  m_lastPing = m_timer.getCurrentTime();
}

BabelClient::~BabelClient()
{
}

void				BabelClient::initMap()
{
  m_map[HEADER] = &BabelClient::onHeader;
  m_map[PING] = &BabelClient::onPing;
  m_map[LOGIN] = &BabelClient::onLogin;
  m_map[LOGOUT] = &BabelClient::onLogout;
  m_map[REGISTER] = &BabelClient::onRegister;
  m_map[CALL] = &BabelClient::onCall;
  m_map[KO_CALL] = &BabelClient::onKOCall;
  m_map[OK_CALL] = &BabelClient::onOKCall;
  m_map[SENDMSG] = &BabelClient::onRecvMsg;
  m_map[HANGOUT] = &BabelClient::onHangout;

  m_headerType.push_back(HEADER);
  m_headerType.push_back(LOGOUT);
  m_headerType.push_back(KO_LOGIN);
  m_headerType.push_back(OK_LOGIN);
  m_headerType.push_back(OK_REGISTER);
  m_headerType.push_back(KO_REGISTER);
  m_headerType.push_back(OK_MSG);
  m_headerType.push_back(PING);
  m_headerType.push_back(KO_MSG);
}

void		BabelClient::onRead(ITcpAsyncClient& /*client*/, char* buffer,
			    std::size_t size)
{
  if (size == 0)
    {
      std::cout << "\033[38m[ server ]\tClient disconnected\033[0m" << std::endl;
      onLogout(NULL);
      return;
    }
  if (m_type != UNKNOWN)
    (this->*m_map[m_type])(buffer);
}

void		BabelClient::onWrite(ITcpAsyncClient& /*client*/, char* /*buffer*/, std::size_t /*size*/)
{
  Buffer       	buf;

  if (!m_queueWrite.empty())
    {
      buf = m_queueWrite.front();
      m_queueWrite.pop();
      memcpy(m_writeBuffer, buf.data, buf.size);
      m_client->write(m_writeBuffer, buf.size);
    }
  else
    {
      m_isWriting = false;
    }
}

ITcpAsyncClient*		BabelClient::getSocket()
{
  return (m_client);
}

void		BabelClient::write(void* data, std::size_t size)
{
  Buffer	buffer;

  if (!m_isWriting)
    {
      memset(m_writeBuffer, 0, 4096);
      memcpy(m_writeBuffer, data, size);
      m_client->write(m_writeBuffer, size);
      m_isWriting = true;
    }
  else
    {
      memset(&buffer, 0, sizeof(Buffer));
      memcpy(buffer.data, data, size);
      buffer.size = size;
      m_queueWrite.push(buffer);
    }
}

void		BabelClient::onTimeout(IAsyncTimer& /*timer*/, bool error)
{
  if (!error)
    delete this;
  else if (m_timer.getCurrentTime() - m_lastPing >= 50000000)
    {
      std::cout << "\033[36mClient Timeouted\033[0m" << std::endl;
      onLogout(NULL);
    }
  else
    {
      sendPing();
      m_timer.wait(1, 0);
    }
}

/* CALLBACKS DU ON READ */

void		BabelClient::onHeader(void *param)
{
  Header	*header = static_cast<Header*>(param);

  std::cout << "\033[36m[ server ]\tCallback HEADER" << header->type << "\033[0m" << std::endl;

  if (m_map.find(header->type) == m_map.end())
    {
      std::cout << "SET THE TYPE TO THE FUCKING UNKNONW" << std::endl;
      m_type = UNKNOWN;
      m_client->read(m_readBuffer, header->size);
    }
  if (std::find(m_headerType.begin(),
		m_headerType.end(), header->type) == m_headerType.end())
    {
      m_type = header->type;
      m_client->read(m_readBuffer, header->size);
    }
  else
    (this->*m_map[header->type])(param);

}

void		BabelClient::onLogin(void *param)
{
  LoginInfo*			loginInfo = static_cast<LoginInfo*>(param);
  std::list<BabelAccountEntry>	accounts = m_server.getAllAccounts();
  std::list<BabelClient*>	clients = m_server.getAllClients();
  std::string			user;
  std::string			md5_pass;

  std::cout << "\033[36m[ server ]\tCallback LOGIN\033[0m" << std::endl;

  loginInfo->user[LOGIN_SIZE - 1] = '\0';
  loginInfo->user[MD5_PASS_SIZE - 1] = '\0';
  user = std::string(loginInfo->user);
  md5_pass = std::string(loginInfo->md5_pass);

  if (m_isConnect == false && m_server.getClient(user) == NULL &&
      m_server.authClient(user, md5_pass))
    {
      m_name = std::string(user);
      m_mdp = std::string(md5_pass);
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
  m_client->read(m_readBuffer, sizeof(Header));
}

void				BabelClient::onPing(void * /*param*/)
{
  std::cout << "\033[36m[ server ]\tON PING\033[0m" << std::endl;

  m_lastPing = m_timer.getCurrentTime();
  m_type = HEADER;
  m_client->read(m_readBuffer, sizeof(Header));
}

void				BabelClient::onRegister(void *param)
{
  BabelAccountEntry	account;
  LoginInfo		*loginInfo = static_cast<LoginInfo*>(param);
  std::string		user;
  std::string		md5_pass;

  std::cout << "\033[36m[ server ]\tCallback REGISTER\033[0m" << std::endl;

  loginInfo->user[LOGIN_SIZE - 1] = '\0';
  loginInfo->user[MD5_PASS_SIZE - 1] = '\0';
  user = std::string(loginInfo->user);
  md5_pass = std::string(loginInfo->md5_pass);

  if (m_isConnect == false && m_server.getClient(user) == NULL &&
      m_server.registerClient(user, md5_pass))
    {
      m_name = user;
      m_mdp = md5_pass;
      m_isConnect = true;
      sendOKRegister();
      sendOKLogin();
      notifyConnexion(param);
      account.login = m_name;
      account.md5pass = m_mdp;
      m_server.addAccount(account);
   }
  else
    {
      m_isConnect = false;
      sendKORegister();
    }
  m_type = HEADER;
  m_client->read(m_readBuffer, sizeof(Header));
}

void			BabelClient::onCall(void *param)
{
  Call*			call = static_cast<Call*>(param);
  UserInfo*		info = static_cast<UserInfo*>(param);
  BabelClient*		client;
  std::string		str_client;

  std::cout << "\033[36m[ server ]\tCallback CALL\033[0m" << std::endl;

  info->user[LOGIN_SIZE - 1] = '\0';
  str_client = std::string(info->user);
  client = m_server.getClient(str_client);

  if (client == NULL)
    return;
  memcpy(info->user, m_name.c_str(), m_name.length() + 1);
  memcpy(call->ip,
	 m_client->getSocket().remote_endpoint().address().to_string().c_str(),
	 m_client->getSocket().remote_endpoint().address().to_string().length() + 1);
  client->sendCall(call);
  m_type = HEADER;
  m_client->read(m_readBuffer, sizeof(Header));
}

void		BabelClient::onKOCall(void * param)
{
  UserInfo	*info = static_cast<UserInfo *>(param);
  BabelClient	*client;
  std::string	str_client;

  std::cout << "\033[36m[ server ]\tCallback KO CALL\033[0m" << std::endl;

  info->user[LOGIN_SIZE - 1] = '\0';
  str_client = std::string(info->user);
  client = m_server.getClient(str_client);

  if (client == NULL)
    return;
  memcpy(info->user, m_name.c_str(), m_name.length() + 1);
  m_type = HEADER;
  info->status = CONNECTED;
  client->sendKOCall(info);
  m_client->read(m_readBuffer, sizeof(Header));
}

void		BabelClient::onOKCall(void * param)
{
  UserInfo	*info = static_cast<UserInfo*>(param);
  BabelClient	*client;
  std::string	str_client;

  std::cout << "\033[36m[ server ]\tCallback OK CALL\033[0m" << std::endl;

  info->user[LOGIN_SIZE - 1] = '\0';
  info->status = CONNECTED;
  str_client = std::string(info->user);
  client = m_server.getClient(str_client);

  memcpy(info->user, m_name.c_str(), m_name.length() + 1);
  m_type = HEADER;
  client->sendOKCall(info);
  m_client->read(m_readBuffer, sizeof(Header));
}

void		BabelClient::onHangout(void* param)
{
  UserInfo*	info = static_cast<UserInfo*>(param);
  BabelClient*	client;
  std::string	user = std::string(info->user);

  std::cout << "\033[36m[ server ]\tCallback HANGOUT\033[0m" << std::endl;

  info->user[LOGIN_SIZE - 1] = '\0';
  user = std::string(info->user);
  client = m_server.getClient(user);

  if (client == NULL)
    return;
  memcpy(info->user, m_name.c_str(), m_name.length() + 1);
  m_type = HEADER;
  info->status = CONNECTED;
  client->sendKOCall(info);
  m_client->read(m_readBuffer, sizeof(Header));
}

void				BabelClient::onRecvMsg(void *param)
{
  BabelClient*			tmp;
  Msg*				msg = static_cast<Msg*>(param);
  std::string			user;

  std::cout << "\033[36m[ server ]\tCallback RECV MSG\033[0m" << std::endl;

  msg->user[LOGIN_SIZE - 1] = '\0';
  msg->msg[MSG_SIZE - 1] = '\0';
  user = std::string(msg->user);

  if ((tmp = m_server.getClient(user)) != NULL)
    {
      memcpy(msg->user, m_name.c_str(), m_name.length() + 1);
      tmp->sendMsg(msg);
      sendOKMsg();
    }
  else
    sendKOMSg();
  m_type = HEADER;
  m_client->read(m_readBuffer, sizeof(Header));
}

void				BabelClient::onLogout(void * /*param*/)
{
  std::cout << "\033[36m[ server ]\tCallback LOGOUT\033[0m" << std::endl;

  notifyLogout();
  m_timer.cancel();
  sendLogout();
  m_client->close();
  m_server.popClient(this);
}

void				BabelClient::notifyLogout()
{
  std::list<BabelClient*>	clients = m_server.getAllClients();
  UserInfo			info;

  memcpy(info.user, m_name.c_str(), LOGIN_SIZE);
  info.status = DISCONNECTED;
  for (std::list<BabelClient*>::iterator it = clients.begin();
       it != clients.end(); it++)
    {
      if ((*it) != this)
	(*it)->sendUserinfo(&info);
    }
}

void				BabelClient::notifyConnexion(void *param)
{
  LoginInfo			*loginInfo = static_cast<LoginInfo*>(param);
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
}

// ANSWSER TO CLIENT

void				BabelClient::sendUserinfo(UserInfo *info)
{
  Header			header;

  std::cout << "\033[31m[ server ]\tSEND USER INFO\033[0m" << std::endl;
  header.type = USERINFO;
  header.size = sizeof(UserInfo);
  write(&header, sizeof(Header));
  write(info, sizeof(UserInfo));
}

void				BabelClient::sendPing()
{
  Header			header;

  std::cout << "\033[33m[ server ]\tSEND PING\033[0m " << m_name << std::endl;
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

void				BabelClient::sendCall(Call *call)
{
  BabelClient*			tmp;
  Header			header;

  std::cout << "\033[31m[ server ]\tSEND CALL\033[0m" << std::endl;
  if ((tmp = m_server.getClient(call->user)) != NULL)
    {
      header.type = CALL;
      header.size = sizeof(Call);
      write(&header, sizeof(Header));
      write(call, sizeof(Call));
    }
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

void				BabelClient::sendOKCall(UserInfo* info)
{
  Header	header;

  std::cout << "\033[31m[ server ]\tOK CALL\033[0m" << std::endl;
  header.type = OK_CALL;
  header.size = sizeof(UserInfo);
  write(&header, sizeof(Header));
  write(info, sizeof(UserInfo));
}

void				BabelClient::sendKOCall(UserInfo* info)
{
  Header			header;

  std::cout << "\033[34m[ server ]\tKO CALL\033[0m" << std::endl;
  header.type = KO_CALL;
  header.size = sizeof(UserInfo);
  write(&header, sizeof(Header));
  write(info, sizeof(UserInfo));

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

void		BabelClient::sendLogout()
{
  Header	header;

  std::cout << "\033[34m[ server ]\tLOGOUT\033[0m" << std::endl;
  header.type = LOGOUT;
  header.size = sizeof(Header);
  write(&header, sizeof(Header));
}
