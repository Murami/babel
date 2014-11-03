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

BabelCoreClient::SizeTypeMap BabelCoreClient::sizeTypeMap = BabelCoreClient::initializeSizeTypeMap();
BabelCoreClient::FunctorTypeMap BabelCoreClient::functorTypeMap = BabelCoreClient::initializeFunctorTypeMap();

BabelCoreClient::BabelCoreClient()
{
  bytesNeeded = sizeof(NET::Header);
  typeNeeded = NET::S_HEADER;
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
  notifyError("test");
}

void BabelCoreClient::onRead()
{
  std::cout << "core data read to read" << std::endl;

  if (m_socket.bytesAvailable() < bytesNeeded)
    return;

  /* lire les data */
  /* prev data type init at header */
  /* if prev data type == header on att un header*/
  /* if header on update prev data type */
  /* else error */
  /* if prev data type == data on att des data */
  /* if data on update prev data type at header on notify les data*/
  /* else error */
}

/* listened view event */

void BabelCoreClient::onUserMsg()
{
  /* on cree un header msg */
  /* on cree une structure msg */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserCall()
{
  /* on vera quand quentin fera port audio */
}

void BabelCoreClient::onUserLogin()
{
  /* on cree un header login */
  /* on cree une structure login */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserLogout()
{
  /* on cree un header logout */
  /* on cree une structure logout */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserRegister()
{
  /* on cree un header register */
  /* on cree une structure register */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserAcceptCall()
{
  /* on cree un header ok_call */
  /* on cree une structure ok_call */
  /* on send le header */
  /* on send la stucture */
}

void BabelCoreClient::onUserDeclineCall()
{
  /* on cree un header ko_call */
  /* on cree une structure ko_call */
  /* on send le header */
  /* on send la stucture */
}

/* core control */

void BabelCoreClient::setTypeNeeded(NET::StructType type)
{
  typeNeeded = type;
}

void BabelCoreClient::setBytesNeeded(quint64 bytes)
{
  bytesNeeded = bytes;
}

BabelCoreClient::SizeTypeMap BabelCoreClient::initializeSizeTypeMap()
{
  SizeTypeMap map;

  map[NET::S_HEADER]	= sizeof(NET::Header);
  map[NET::S_LOGIN]	= sizeof(NET::LoginInfo);
  map[NET::S_USER]	= sizeof(NET::UserInfo);
  map[NET::S_CALL]	= sizeof(NET::CallInfo);
  map[NET::S_MSG]	= sizeof(NET::MsgInfo);

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

/* socket control */

void BabelCoreClient::read()
{
  m_socket.read();
}

void BabelCoreClient::write(void * data)
{
  m_socket.write(data);
}

void BabelCoreClient::connect(QString address, quint16 port)
{
  m_socket.connect(address, port);
}

void BabelCoreClient::disconnect()
{
  m_socket.disconnect();
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

void BabelCoreClient::notifyError(char * error)
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
