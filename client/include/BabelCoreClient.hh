#ifndef BABEL_CORE_CLIENT_HH
#define BABEL_CORE_CLIENT_HH

#include <list>

#include "IAsyncSocketListener.hh"
#include "ICoreListener.hh"
#include "IWidgetListener.hh"
#include "QTcpAsyncSocket.hh"
#include "IFunctor.hh"
#include "Protocol.hh"

class ICallListener;
class IConnectListener;
class IDisconnectListener;
class IErrorListener;
class ICallErrorListener;
class ILoginListener;
class IRegisterListener;
class IMsgListener;
class IMsgErrorListener;
class IUserInfoListener;

class BabelCoreClient : private IAsyncSocketListener, public IWidgetListener
{
Q_OBJECT

public:
  BabelCoreClient();
  ~BabelCoreClient();

public slots:
  void onConnect();
  void onDisconnect();
  void onError(QAbstractSocket::SocketError error);
  void onRead();

public:
  void onUserMsg();
  void onUserCall();
  void onUserLogin();
  void onUserLogout();
  void onUserRegister();
  void onUserAcceptCall();
  void onUserDeclineCall();

public:
  void read();
  void write(void * data);
  void connect(QString address, quint16 port);
  void disconnect();
  void setTypeNeeded(NET::Type type);
  void setBytesNeeded(quint64 bytes);

  void addCallListener(ICallListener * listener);
  void addConnectListener(IConnectListener * listener);
  void addDisconnectListener(IDisconnectListener * listener);
  void addErrorListener(IErrorListener * listener);
  void addCallErrorListener(ICallErrorListener * listener);
  void addLoginListener(ILoginListener * listener);
  void addRegisterListener(IRegisterListener * listener);
  void addMsgListener(IMsgListener * listener);
  void addMsgErrorListener(IMsgErrorListener * listener);
  void addUserInfoListener(IUserInfoListener * listener);

private:
  void notifyCall(NET::CallInfo info);
  void notifyConnect(void);
  void notifyDisconnect(void);
  void notifyError(char * error);
  void notifyCallError(bool rep);
  void notifyLogin(bool rep);
  void notifyRegister(bool rep);
  void notifyMsg(NET::MsgInfo info);
  void notifyMsgError(bool rep);
  void notifyUserInfo(NET::UserInfo info);

private:
  QTcpAsyncSocket			m_socket;
  quint64				bytesNeeded;
  NET::Type				typeNeeded;
  std::map<NET::Type, size_t>		sizeTypeMap;
  std::map<NET::Type, IFunctor *>	functorTypeMap;

  std::list<ICallListener *>		CallListenerList;
  std::list<IConnectListener *>		ConnectListenerList;
  std::list<IDisconnectListener *>	DisconnectListenerList;
  std::list<IErrorListener *>		ErrorListenerList;
  std::list<ICallErrorListener *>	CallErrorListenerList;
  std::list<ILoginListener *>		LoginListenerList;
  std::list<IRegisterListener *>	RegisterListenerList;
  std::list<IMsgListener *>		MsgListenerList;
  std::list<IMsgErrorListener *>	MsgErrorListenerList;
  std::list<IUserInfoListener *>	UserInfoListenerList;
};

#endif
