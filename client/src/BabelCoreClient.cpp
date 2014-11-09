#include <sstream>
#include <QHostAddress>
#include <QSettings>
#include <cstring>
#include <exception>
#include <stdexcept>

#include "IKoCallListener.hh"
#include "BabelCoreClient.hh"
#include "ICallErrorListener.hh"
#include "IConnectListener.hh"
#include "IDisconnectListener.hh"
#include "IMsgErrorListener.hh"
#include "IRegisterListener.hh"
#include "ICallListener.hh"
#include "IErrorListener.hh"
#include "ILoginListener.hh"
#include "IMsgListener.hh"
#include "IUserInfoListener.hh"
#include "Functor.hh"
#include "PAAudioService.hh"

BabelCoreClient::SizeTypeMap BabelCoreClient::sizeTypeMap	= BabelCoreClient::initializeSizeTypeMap();
BabelCoreClient::FunctorTypeMap BabelCoreClient::functorTypeMap = BabelCoreClient::initializeFunctorTypeMap();
BabelCoreClient::ErrorMap BabelCoreClient::errorMap		= BabelCoreClient::initializeErrorMap();

BabelCoreClient::BabelCoreClient()
{
  typeNeeded = NET::T_HEADER;

  m_socket.addListener(this);
  m_audio_socket_read.addListener(this);
  PAAudioService::getInstance()->initialize();
  m_player = new AudioPlayer;
  m_recorder = new AudioRecorder(*this);
  m_isConnected = false;
}

BabelCoreClient::~BabelCoreClient()
{
  PAAudioService::getInstance()->release();
}

/* listened Tcp socket event*/

void BabelCoreClient::onTcpConnect()
{
  notifyConnect();
}

void BabelCoreClient::onTcpDisconnect()
{
}

void BabelCoreClient::onTcpError(int error)
{
  notifyError(errorMap[error]);
}

void BabelCoreClient::onTcpRead()
{
  while (m_socket.bytesAvailable() >= sizeTypeMap[typeNeeded])
    {
      m_socket.read(buffer, sizeTypeMap[typeNeeded]);
      if (typeNeeded == NET::T_HEADER)
	{
	  NET::Header* tmp = reinterpret_cast<NET::Header*>(buffer);
	  (*functorTypeMap[tmp->type])(*this, buffer);
	}
      else
	(*functorTypeMap[typeNeeded])(*this, buffer);
    }
}

/* listened Udp socket event */

void BabelCoreClient::onUdpError(int e)
{
  std::stringstream ss;

  ss << e;
  throw std::runtime_error("UDP ERROR : " + ss.str());
}

void BabelCoreClient::onUdpRead()
{
  NET::SamplePacket packet;

  while (m_audio_socket_read.hasPendingDatagrams() &&
  	 m_audio_socket_read.pendingDatagramSize() >= static_cast<int>(sizeof(NET::SamplePacket)))
    {
      std::string str;
      uint16_t port;

      m_audio_socket_read.readDatagram(&packet, sizeof(packet), &str, &port);
      try
	{
	  m_player->pushFrames(packet.sample.rawData, packet.sample.size);
	}
      catch (const std::exception& e)
	{
	  std::cout << "AudioPlayer::pushFrames : " << e.what() << std::endl;
	}
    }
}

/* listened view event */

void BabelCoreClient::onUserMsg(QString login, QString msg)
{
  NET::Header		header;
  NET::MsgInfo		info;
  std::string		s_msg;
  std::string::iterator it;
  std::string::iterator start;

  s_msg = msg.toStdString();
  it = s_msg.begin();

  header.type = NET::T_SENDMSG;
  header.size = sizeof(NET::Header);
  header.size = sizeof(info);

  memcpy(info.user, login.toStdString().c_str(), login.length() + 1);

  while (it != s_msg.end())
    {
      int	i;

      for (i = 0; i != MSG_SIZE - 1 && it != s_msg.end(); i++, it++)
	info.msg[i] = *it;
      info.msg[i] = '\0';
      m_socket.write(&header, sizeof(NET::Header));
      m_socket.write(&info, sizeof(info));
    }
}

void BabelCoreClient::onUserCall(QString login)
{
  NET::Header		header;
  NET::CallInfo		info;

  m_udpAddress = "0.0.0.0"; //like QHostAddress::AnyIpv4
  m_udpPort = 1235;

  header.type = NET::T_CALL;
  header.size = sizeof(info);
  memcpy(info.user, login.toStdString().c_str(), login.length() + 1);
  memset(info.ip, 0, IP_SIZE);
  info.port = 1235;
  info.prot = NET::UDP;
  info.type = NET::AUDIO;
  m_socket.write(&header, sizeof(header));
  m_socket.write(&info, sizeof(info));
}

void BabelCoreClient::onUserLogin(QString login, QString pass)
{
  NET::Header		header;
  NET::LoginInfo	info;

  this->connect();

  QString md5_pass = QString(QCryptographicHash::hash(pass.toUtf8(),QCryptographicHash::Md5).toHex());

  header.type = NET::T_LOGIN;
  header.size = sizeof(info);
  memcpy(info.user, login.toStdString().c_str(), login.length() + 1);
  memcpy(info.md5_pass, md5_pass.toStdString().c_str(), MD5_PASS_SIZE);
  m_socket.write(&header, sizeof(header));
  m_socket.write(&info, sizeof(info));
}

void BabelCoreClient::onUserLogout(void)
{
  NET::Header header;

  header.type = NET::T_LOGOUT;
  header.size = 0;
  m_socket.write(&header, sizeof(header));
  this->disconnect();
}

void BabelCoreClient::onUserRegister(QString login, QString pass)
{
  NET::Header		header;
  NET::LoginInfo	info;

  this->connect();

  QString md5_pass = QString(QCryptographicHash::hash(pass.toUtf8(),QCryptographicHash::Md5).toHex());

  header.type = NET::T_REGISTER;
  header.size = sizeof(info);
  memcpy(info.user, login.toStdString().c_str(), login.length() + 1);
  memcpy(info.md5_pass, md5_pass.toStdString().c_str(), MD5_PASS_SIZE);
  m_socket.write(&header, sizeof(header));
  m_socket.write(&info, sizeof(info));
}

void BabelCoreClient::onUserAcceptCall(QString login)
{
  NET::Header	header;
  NET::UserInfo info;

  header.type = NET::T_OK_CALL;
  header.size = sizeof(info);
  memcpy(info.user, login.toStdString().c_str(), login.length() + 1);
  info.status = NET::CONNECTED;
  m_socket.write(&header, sizeof(NET::Header));
  m_socket.write(&info, sizeof(info));

  connectAudio();

  if (m_recorder->active() == false)
    m_recorder->start();
  if (m_player->active() == false)
    m_player->start();
}

void BabelCoreClient::onUserDeclineCall(QString login)
{
  NET::Header	header;
  NET::UserInfo info;
  header.type = NET::T_KO_CALL;
  header.size = sizeof(info);
  memcpy(info.user, login.toStdString().c_str(), login.length() + 1);
  info.status = NET::CONNECTED;
  m_socket.write(&header, sizeof(NET::Header));
  m_socket.write(&info, sizeof(info));
}

void BabelCoreClient::onUserHangout(QString login)
{
  NET::Header	header;
  NET::UserInfo info;

  header.type = NET::T_HANGOUT;
  header.size = sizeof(info);
  memcpy(info.user, login.toStdString().c_str(), login.length() + 1);
  info.status = NET::CONNECTED;
  m_socket.write(&header, sizeof(NET::Header));
  m_socket.write(&info, sizeof(info));
  if (m_player->active() == true)
    m_player->stop();
  if (m_recorder->active() == true)
    m_recorder->stop();
  disconnectAudio();
}

void BabelCoreClient::onPing()
{
  NET::Header	header;

  header.type = NET::T_PING;
  header.size = sizeof(NET::Header);
  m_socket.write(&header, sizeof(NET::Header));
}

/* core control */

void BabelCoreClient::sendAudioFrame(void* frame, int size)
{
  NET::Sample		sample;
  NET::SamplePacket	packet;

  // std::string addr("255.255.255.255");
  packet.sample.size = size;
  packet.header.size = sizeof(sample);
  packet.header.type = NET::T_SAMPLE;
  memcpy(&packet.sample.rawData, frame, size);
  m_audio_socket_read.writeDatagram(&packet, sizeof(NET::SamplePacket), m_udpAddress, m_udpPort);
}

void BabelCoreClient::connectAudio()
{
  m_audio_socket_read.bind(m_udpPort);
}

void BabelCoreClient::disconnectAudio()
{
  m_audio_socket_read.close();
}

void BabelCoreClient::connect()
{
  QSettings *settings = new QSettings("setting.ini", QSettings::IniFormat);
  QString address("127.0.0.1");
  uint16_t port(1234);

  if (!m_isConnected)
    {
      if (settings->contains("ip") == true)
	address = settings->value("ip").toString();

      if (settings->contains("port") == true)
	port = settings->value("port").toUInt();

      m_socket.connect(address.toStdString(), port);
      m_isConnected = true;
    }
}

void BabelCoreClient::disconnect()
{
  m_isConnected = false;
  if (m_player->active() == true)
    m_player->stop();
  if (m_recorder->active() == true)
    m_recorder->stop();
  m_socket.disconnect();
}

void BabelCoreClient::setTypeNeeded(NET::Type type)
{
  typeNeeded = type;
}

NET::Type BabelCoreClient::getTypeNeeded()
{
  return (typeNeeded);
}

AudioRecorder* BabelCoreClient::getRecorder()
{
  return (m_recorder);
}

AudioPlayer* BabelCoreClient::getPlayer()
{
  return (m_player);
}

std::string BabelCoreClient::getUdpAddress()
{
  return (m_udpAddress);
}

uint16_t BabelCoreClient::getUdpPort()
{
  return (m_udpPort);
}

void BabelCoreClient::setUdpAddress(std::string address)
{
  m_udpAddress = address;
}

void BabelCoreClient::setUdpPort(uint16_t port)
{
  m_udpPort = port;
}

/* initialize core constant */

BabelCoreClient::SizeTypeMap BabelCoreClient::initializeSizeTypeMap()
{
  SizeTypeMap map;

  map[NET::T_HEADER]	= sizeof(NET::Header);
  map[NET::T_USERINFO]	= sizeof(NET::UserInfo);
  map[NET::T_CALL]	= sizeof(NET::CallInfo);
  map[NET::T_RECVMSG]	= sizeof(NET::MsgInfo);

  return (map);
}

BabelCoreClient::FunctorTypeMap BabelCoreClient::initializeFunctorTypeMap()
{
  FunctorTypeMap map;

  map[NET::T_USERINFO] = new UserInfoFunctor;
  map[NET::T_RECVMSG] = new RecvMsgFunctor;
  map[NET::T_CALL] = new CallFunctor;
  map[NET::T_OK_LOGIN] = new OkLoginFunctor;
  map[NET::T_KO_LOGIN] = new KoLoginFunctor;
  map[NET::T_OK_REGISTER] = new OkRegisterFunctor;
  map[NET::T_KO_REGISTER] = new KoRegisterFunctor;
  map[NET::T_OK_CALL] = new OkCallFunctor;
  map[NET::T_KO_CALL] = new KoCallFunctor;
  map[NET::T_OK_MSG] = new OkMsgFunctor;
  map[NET::T_KO_MSG] = new KoMsgFunctor;
  map[NET::T_SAMPLE] = new SampleFunctor;
  map[NET::T_IMG] = new ImgFunctor;
  map[NET::T_PING] = new PingFunctor;

  return (map);
}

BabelCoreClient::ErrorMap BabelCoreClient::initializeErrorMap()
{
  ErrorMap map;

  map[QAbstractSocket::ConnectionRefusedError] =  "The connection was refused by the peer (or timed out).";
  map[QAbstractSocket::RemoteHostClosedError] =  "Error The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.";
  map[QAbstractSocket::HostNotFoundError] = "The host address was not found.";
  map[QAbstractSocket::SocketAccessError] = "The socket operation failed because the application lacked the required privileges.";
  map[QAbstractSocket::SocketResourceError] = "The local system ran out of resources (e.g., too many sockets).";
  map[QAbstractSocket::SocketTimeoutError] = "The socket operation timed out.";
  map[QAbstractSocket::DatagramTooLargeError] = "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
  map[QAbstractSocket::NetworkError] = "An error occurred with the network (e.g., the network cable was accidentally plugged out).";
  map[QAbstractSocket::AddressInUseError] = "The address specified to QUdpSocket::bind() is already in use and was set to be exclusive.";
  map[QAbstractSocket::SocketAddressNotAvailableError] = "The address specified to QUdpSocket::bind() does not belong to the host.";
  map[QAbstractSocket::UnsupportedSocketOperationError] = "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).";
  map[QAbstractSocket::ProxyAuthenticationRequiredError] = "The socket is using a proxy, and the proxy requires authentication.";
  map[QAbstractSocket::SslHandshakeFailedError] = "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket) (This value was introduced in 4.4.)";
  map[QAbstractSocket::UnfinishedSocketOperationError] = "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background). (This value was introduced in 4.4.)";
  map[QAbstractSocket::ProxyConnectionRefusedError] = "Could not contact the proxy server because the connection to that server was denied (This value was introduced in 4.5.)";
  map[QAbstractSocket::ProxyConnectionClosedError] = "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established) (This value was introduced in 4.5.)";
  map[QAbstractSocket::ProxyConnectionTimeoutError] = "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase. (This value was introduced in 4.5.)";
  map[QAbstractSocket::ProxyNotFoundError] = "The proxy address set with setProxy() (or the application proxy) was not found. (This value was introduced in 4.5.)";
  map[QAbstractSocket::ProxyProtocolError] = "The connection negotiation with the proxy server because the response from the proxy server could not be understood. (This value was introduced in 4.5.)";
  map[QAbstractSocket::UnknownSocketError] = "An unidentified error occurred.";

  return (map);
}

/* add listener */

void BabelCoreClient::addCallListener(ICallListener * listener)
{
  CallListenerList.push_front(std::pair<bool, ICallListener*>(true, listener));
}

void BabelCoreClient::addConnectListener(IConnectListener * listener)
{
  ConnectListenerList.push_front(std::pair<bool, IConnectListener*>(true, listener));
}

void BabelCoreClient::addDisconnectListener(IDisconnectListener * listener)
{
  DisconnectListenerList.push_front(std::pair<bool, IDisconnectListener*>(true, listener));
}

void BabelCoreClient::addErrorListener(IErrorListener * listener)
{
  ErrorListenerList.push_front(std::pair<bool, IErrorListener*>(true, listener));
}

void BabelCoreClient::addCallErrorListener(ICallErrorListener * listener)
{
  CallErrorListenerList.push_front(std::pair<bool, ICallErrorListener*>(true, listener));
}

void BabelCoreClient::addLoginListener(ILoginListener * listener)
{
  LoginListenerList.push_front(std::pair<bool, ILoginListener*>(true, listener));
}

void BabelCoreClient::addRegisterListener(IRegisterListener * listener)
{
  RegisterListenerList.push_front(std::pair<bool, IRegisterListener*>(true, listener));
}

void BabelCoreClient::addMsgListener(IMsgListener * listener)
{
  MsgListenerList.push_front(std::pair<bool, IMsgListener*>(true, listener));
}

void BabelCoreClient::addMsgErrorListener(IMsgErrorListener * listener)
{
  MsgErrorListenerList.push_front(std::pair<bool, IMsgErrorListener*>(true, listener));
}

void BabelCoreClient::addUserInfoListener(IUserInfoListener * listener)
{
  UserInfoListenerList.push_front(std::pair<bool, IUserInfoListener*>(true, listener));
}

void BabelCoreClient::addKoCallListener(IKoCallListener * listener)
{
  KoCallListenerList.push_front(std::pair<bool, IKoCallListener*>(true, listener));
}

/* delete listener */

void BabelCoreClient::deleteCallListener(ICallListener * listener)
{
  std::list<std::pair<bool, ICallListener *> >::iterator it;

  it = CallListenerList.begin();
  for (; it != CallListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteConnectListener(IConnectListener * listener)
{
  std::list<std::pair<bool, IConnectListener *> >::iterator it;

  it = ConnectListenerList.begin();
  for (; it != ConnectListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteDisconnectListener(IDisconnectListener * listener)
{
  std::list<std::pair<bool, IDisconnectListener *> >::iterator it;

  it = DisconnectListenerList.begin();
  for (; it != DisconnectListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteErrorListener(IErrorListener * listener)
{
  std::list<std::pair<bool, IErrorListener *> >::iterator it;

  it = ErrorListenerList.begin();
  for (; it != ErrorListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteCallErrorListener(ICallErrorListener * listener)
{
  std::list<std::pair<bool, ICallErrorListener *> >::iterator it;

  it = CallErrorListenerList.begin();
  for (; it != CallErrorListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteLoginListener(ILoginListener * listener)
{
  std::list<std::pair<bool, ILoginListener *> >::iterator it;

  it = LoginListenerList.begin();
  for (; it != LoginListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteRegisterListener(IRegisterListener * listener)
{
  std::list<std::pair<bool, IRegisterListener *> >::iterator it;

  it = RegisterListenerList.begin();
  for (; it != RegisterListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteMsgListener(IMsgListener * listener)
{
  std::list<std::pair<bool, IMsgListener *> >::iterator it;

  it = MsgListenerList.begin();
  for (; it != MsgListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteMsgErrorListener(IMsgErrorListener * listener)
{
  std::list<std::pair<bool, IMsgErrorListener *> >::iterator it;

  it = MsgErrorListenerList.begin();
  for (; it != MsgErrorListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteUserInfoListener(IUserInfoListener * listener)
{
  std::list<std::pair<bool, IUserInfoListener *> >::iterator it;

  it = UserInfoListenerList.begin();
  for (; it != UserInfoListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

void BabelCoreClient::deleteKoCallListener(IKoCallListener * listener)
{
  std::list<std::pair<bool, IKoCallListener *> >::iterator it;

  it = KoCallListenerList.begin();
  for (; it != KoCallListenerList.end(); it++)
    if ((*it).second == listener)
      (*it).first = false;
}

/* notify listener */

void BabelCoreClient::notifyKoCall()
{
  std::list<std::pair<bool, IKoCallListener *> >::iterator it;

  it = KoCallListenerList.begin();
  for (; it != KoCallListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onKoCall();
}

void BabelCoreClient::notifyCall(NET::CallInfo info)
{
  std::list<std::pair<bool, ICallListener *> >::iterator it;

  it = CallListenerList.begin();
  for (; it != CallListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onCall(info);
}

void BabelCoreClient::notifyConnect(void)
{
  std::list<std::pair<bool, IConnectListener *> >::iterator it;

  it = ConnectListenerList.begin();
  for (; it != ConnectListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onConnect();
}

void BabelCoreClient::notifyDisconnect(void)
{
  std::list<std::pair<bool, IDisconnectListener *> >::iterator it;

  it = DisconnectListenerList.begin();
  for (; it != DisconnectListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onDisconnect();
}

void BabelCoreClient::notifyError(QString error)
{
  std::list<std::pair<bool, IErrorListener *> >::iterator it;

  it = ErrorListenerList.begin();
  for (; it != ErrorListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onError(error);
}

void BabelCoreClient::notifyCallError(bool rep, NET::UserInfo)
{
  std::list<std::pair<bool, ICallErrorListener *> >::iterator it;

  it = CallErrorListenerList.begin();
  for (; it != CallErrorListenerList.end(); it++)
    if ((*it).first == true)
      (*it).second->onCallError(rep);
}

void BabelCoreClient::notifyLogin(bool rep)
{
  std::list<std::pair<bool, ILoginListener *> >::iterator it;

  it = LoginListenerList.begin();
  for (; it != LoginListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onLogin(rep);
}

void BabelCoreClient::notifyRegister(bool rep)
{
  std::list<std::pair<bool, IRegisterListener *> >::iterator it;

  it = RegisterListenerList.begin();
  for (; it != RegisterListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onRegister(rep);
}

void BabelCoreClient::notifyMsg(NET::MsgInfo info)
{
  std::list<std::pair<bool, IMsgListener *> >::iterator it;

  it = MsgListenerList.begin();
  for (; it != MsgListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onMsg(info);
}

void BabelCoreClient::notifyMsgError(bool rep)
{
  std::list<std::pair<bool, IMsgErrorListener *> >::iterator it;

  it = MsgErrorListenerList.begin();
  for (; it != MsgErrorListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onMsgError(rep);
}

void BabelCoreClient::notifyUserInfo(NET::UserInfo info)
{
  std::list<std::pair<bool, IUserInfoListener *> >::iterator it;

  it = UserInfoListenerList.begin();
  for (; it != UserInfoListenerList.end(); ++it)
    if ((*it).first == true)
      (*it).second->onUserInfo(info);
}
