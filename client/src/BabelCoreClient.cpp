#include "BabelCoreClient.hh"

BabelCoreClient::BabelCoreClient()
{
  bytesNeeded = sizeof(NET::Header);
  typeNeeded = NET::HEADER;
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

void BabelCoreClient::setTypeNeeded(NET::Type type)
{
  typeNeeded = type;
}

void BabelCoreClient::setBytesNeeded(quint64 bytes)
{
  bytesNeeded = bytes;
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

}

void BabelCoreClient::notifyDisconnect(void)
{

}

void BabelCoreClient::notifyError(char * error)
{

}

void BabelCoreClient::notifyCallError(bool rep)
{

}

void BabelCoreClient::notifyLogin(bool rep)
{

}

void BabelCoreClient::notifyRegister(bool rep)
{

}

void BabelCoreClient::notifyMsg(NET::MsgInfo info)
{

}

void BabelCoreClient::notifyMsgError(bool rep)
{

}

void BabelCoreClient::notifyUserInfo(NET::UserInfo info)
{

}
