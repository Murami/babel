#include <QSettings>

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

BabelCoreClient::SizeTypeMap BabelCoreClient::sizeTypeMap	= BabelCoreClient::initializeSizeTypeMap();
BabelCoreClient::FunctorTypeMap BabelCoreClient::functorTypeMap = BabelCoreClient::initializeFunctorTypeMap();
BabelCoreClient::ErrorMap BabelCoreClient::errorMap		= BabelCoreClient::initializeErrorMap();

BabelCoreClient::BabelCoreClient()
{
  typeNeeded = NET::T_HEADER;
  QObject::connect(&m_socket, SIGNAL(notifyRead()), this, SLOT(onRead()));
  QObject::connect(&m_socket, SIGNAL(notifyConnect()), this, SLOT(onConnect()));
  QObject::connect(&m_socket, SIGNAL(notifyDisconnect()), this, SLOT(onDisconnect()));
  QObject::connect(&m_socket, SIGNAL(notifyError(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

BabelCoreClient::~BabelCoreClient()
{

}

/* listened socket event*/

void BabelCoreClient::onConnect()
{
  std::cout << "core connect detected" << std::endl;
  notifyConnect();
}

void BabelCoreClient::onDisconnect()
{
  std::cout << "core fisconnect detected" << std::endl;
  notifyDisconnect();
}

void BabelCoreClient::onError(QAbstractSocket::SocketError error)
{
  std::cout << "core error detected" << std::endl;

  notifyError(errorMap[error]);
}

void BabelCoreClient::onRead()
{
  std::cout << "core data read to read" << std::endl;

  if (m_socket.bytesAvailable() < sizeTypeMap[typeNeeded])
    return;
  m_socket.read(buffer,sizeTypeMap[typeNeeded]);
  if (typeNeeded == NET::T_HEADER)
    {
      NET::Header* tmp = reinterpret_cast<NET::Header*>(buffer);
      (*functorTypeMap[tmp->type])(*this, buffer);
    }
  else
    {
      (*functorTypeMap[typeNeeded])(*this, buffer);
    }
}

/* listened view event */

void BabelCoreClient::onUserMsg(QString login, QString msg)
{
  std::cout << __FUNCTION__ << std::endl;
  /* on cree un header msg */
  /* on cree une structure msg */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserCall(QString login)
{
  std::cout << __FUNCTION__ << std::endl;
  /* on vera quand quentin fera port audio */
}

void BabelCoreClient::onUserLogin(QString login, QString pass)
{
  std::cout << __FUNCTION__ << std::endl;
  /* on cree un header login */
  /* on cree une structure login */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserLogout(void)
{
  std::cout << __FUNCTION__ << std::endl;
  /* on cree un header logout */
  /* on cree une structure logout */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserRegister(QString login, QString pass)
{
  std::cout << __FUNCTION__ << std::endl;
  /* on cree un header register */
  /* on cree une structure register */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserAcceptCall(QString login)
{
  std::cout << __FUNCTION__ << std::endl;
  /* on cree un header ok_call */
  /* on cree une structure ok_call */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserDeclineCall(QString login)
{
  std::cout << __FUNCTION__ << std::endl;
  /* on cree un header ko_call */
  /* on cree une structure ko_call */
  /* on send le header */
  /* on send la stucture */
}

/* core control */

void BabelCoreClient::run()
{
  QSettings *settings = new QSettings("setting.ini", QSettings::IniFormat);
  QString address("127.0.0.1");
  quint16 port(1234);

  if (settings->contains("ip") == true)
    address = settings->value("ip").toString();

  if (settings->contains("port") == true)
    port = settings->value("port").toUInt();

  m_socket.connect(address, port);
}

void BabelCoreClient::setTypeNeeded(NET::Type type)
{
  typeNeeded = type;
}

NET::Type BabelCoreClient::getTypeNeeded()
{
  return (typeNeeded);
}

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
  CallListenerList.push_front(listener);
}

void BabelCoreClient::addConnectListener(IConnectListener * listener)
{
  ConnectListenerList.push_front(listener);
}

void BabelCoreClient::addDisconnectListener(IDisconnectListener * listener)
{
  DisconnectListenerList.push_front(listener);
}

void BabelCoreClient::addErrorListener(IErrorListener * listener)
{
  ErrorListenerList.push_front(listener);
}

void BabelCoreClient::addCallErrorListener(ICallErrorListener * listener)
{
  CallErrorListenerList.push_front(listener);
}

void BabelCoreClient::addLoginListener(ILoginListener * listener)
{
  LoginListenerList.push_front(listener);
}

void BabelCoreClient::addRegisterListener(IRegisterListener * listener)
{
  RegisterListenerList.push_front(listener);
}

void BabelCoreClient::addMsgListener(IMsgListener * listener)
{
  MsgListenerList.push_front(listener);
}

void BabelCoreClient::addMsgErrorListener(IMsgErrorListener * listener)
{
  MsgErrorListenerList.push_front(listener);
}

void BabelCoreClient::addUserInfoListener(IUserInfoListener * listener)
{
  UserInfoListenerList.push_front(listener);
}

/* notify listener */

void BabelCoreClient::notifyCall(NET::CallInfo info)
{
  std::list<ICallListener *>::iterator it;

  it = CallListenerList.begin();
  for (; it != CallListenerList.end(); ++it)
    (*it)->onData(info);
}

void BabelCoreClient::notifyConnect(void)
{
  std::list<IConnectListener *>::iterator it;

  it = ConnectListenerList.begin();
  for (; it != ConnectListenerList.end(); ++it)
    (*it)->onData();
}

void BabelCoreClient::notifyDisconnect(void)
{
  std::list<IDisconnectListener *>::iterator it;

  it = DisconnectListenerList.begin();
  for (; it != DisconnectListenerList.end(); ++it)
    (*it)->onData();
}

void BabelCoreClient::notifyError(QString error)
{
  std::list<IErrorListener *>::iterator it;

  it = ErrorListenerList.begin();
  for (; it != ErrorListenerList.end(); ++it)
    (*it)->onData(error);
}

void BabelCoreClient::notifyCallError(bool rep)
{
  std::list<ICallErrorListener *>::iterator it;

  it = CallErrorListenerList.begin();
  for (; it != CallErrorListenerList.end(); ++it)
    (*it)->onData(rep);
}

void BabelCoreClient::notifyLogin(bool rep)
{
  std::list<ILoginListener *>::iterator it;

  it = LoginListenerList.begin();
  for (; it != LoginListenerList.end(); ++it)
    (*it)->onData(rep);
}

void BabelCoreClient::notifyRegister(bool rep)
{
  std::list<IRegisterListener *>::iterator it;

  it = RegisterListenerList.begin();
  for (; it != RegisterListenerList.end(); ++it)
    (*it)->onData(rep);
}

void BabelCoreClient::notifyMsg(NET::MsgInfo info)
{
  std::list<IMsgListener *>::iterator it;

  it = MsgListenerList.begin();
  for (; it != MsgListenerList.end(); ++it)
    (*it)->onData(info);
}

void BabelCoreClient::notifyMsgError(bool rep)
{
  std::list<IMsgErrorListener *>::iterator it;

  it = MsgErrorListenerList.begin();
  for (; it != MsgErrorListenerList.end(); ++it)
    (*it)->onData(rep);
}

void BabelCoreClient::notifyUserInfo(NET::UserInfo info)
{
  std::list<IUserInfoListener *>::iterator it;

  it = UserInfoListenerList.begin();
  for (; it != UserInfoListenerList.end(); ++it)
    (*it)->onData(info);
}
