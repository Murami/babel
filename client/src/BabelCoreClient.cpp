#include "BabelCoreClient.hh"

BabelCoreClient::BabelCoreClient()
{
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
  notifyError();
}

void BabelCoreClient::onRead()
{
  std::cout << "core data read to read" << std::endl;

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

void BabelCoreClient::addUserInfoListener(ICoreListener * listener)
{
  UserInfoListenerList.push_front(listener);
}

void BabelCoreClient::addCallListener(ICoreListener * listener)
{
  CallListenerList.push_front(listener);
}

void BabelCoreClient::addHangoutListener(ICoreListener * listener)
{
  HangoutListenerList.push_front(listener);
}

void BabelCoreClient::addMsgListener(ICoreListener * listener)
{
  MsgListenerList.push_front(listener);
}

void BabelCoreClient::addConnectListener(ICoreListener * listener)
{
  ConnectListenerList.push_front(listener);
}

void BabelCoreClient::addDisconnectListener(ICoreListener * listener)
{
  DisconnectListenerList.push_front(listener);
}

void BabelCoreClient::addErrorListener(ICoreListener * listener)
{
  ErrorListenerList.push_front(listener);
}

/* notify listener */

void  BabelCoreClient::notifyCall()
{
  std::list<ICoreListener* >::iterator it;

  it = CallListenerList.begin();
  for( ; it != CallListenerList.end(); it++)
    (*it)->onData();
}

void BabelCoreClient::notifyMsg()
{
  std::list<ICoreListener* >::iterator it;

  it = MsgListenerList.begin();
  for( ; it != MsgListenerList.end(); it++)
    (*it)->onData();
}

void BabelCoreClient::notifyHangout()
{
  std::list<ICoreListener* >::iterator it;

  it = HangoutListenerList.begin();
  for( ; it != HangoutListenerList.end(); it++)
    (*it)->onData();
}

void BabelCoreClient::notifyUserInfo()
{
  std::list<ICoreListener* >::iterator it;

  it = UserInfoListenerList.begin();
  for( ; it != UserInfoListenerList.end(); it++)
    (*it)->onData();
}

void BabelCoreClient::notifyConnect()
{
  std::list<ICoreListener* >::iterator it;

  it = ConnectListenerList.begin();
  for( ; it != ConnectListenerList.end(); it++)
    (*it)->onData();
}

void BabelCoreClient::notifyDisconnect()
{
  std::list<ICoreListener* >::iterator it;

  it = DisconnectListenerList.begin();
  for( ; it != DisconnectListenerList.end(); it++)
    (*it)->onData();
}

void BabelCoreClient::notifyError()
{
  std::list<ICoreListener* >::iterator it;

  it = ErrorListenerList.begin();
  for( ; it != ErrorListenerList.end(); it++)
    (*it)->onData();
}
