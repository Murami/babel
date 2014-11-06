#ifndef BABEL_CORE_CLIENT_HH
# define BABEL_CORE_CLIENT_HH

# include <list>
# include <QString>

# include "ITcpAsyncSocketListener.hh"
# include "IWidgetListener.hh"
# include "ITimerListener.hh"
# include "TcpAsyncSocket.hh"
# include "IFunctor.hh"
# include "Protocol.hh"
# include "Timer.hh"

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

class BabelCoreClient : public ITcpAsyncSocketListener, public IWidgetListener, public ITimerListener
{
private:
  typedef std::map<NET::Type, size_t>				SizeTypeMap;
  typedef std::map<NET::Type, IFunctor *>			FunctorTypeMap;
  typedef std::map<int, QString>				ErrorMap;

public:
  BabelCoreClient();
  ~BabelCoreClient();

public:
  void			onConnect();
  void			onDisconnect();
  void			onError(int error);
  void			onRead();

public:
  void			onTimeout(int id);

public:
  void			onUserMsg(QString login, QString msg);
  void			onUserCall(QString login);
  void			onUserLogin(QString login, QString pass);
  void			onUserLogout(void);
  void			onUserRegister(QString login, QString pass);
  void			onUserAcceptCall(QString login);
  void			onUserDeclineCall(QString login);
  void			onUserHangout(QString login);

public:
  void			run();
  void			setTypeNeeded(NET::Type type);
  NET::Type		getTypeNeeded();

  void			addCallListener(ICallListener * listener);
  void			addConnectListener(IConnectListener * listener);
  void			addDisconnectListener(IDisconnectListener * listener);
  void			addErrorListener(IErrorListener * listener);
  void			addCallErrorListener(ICallErrorListener * listener);
  void			addLoginListener(ILoginListener * listener);
  void			addRegisterListener(IRegisterListener * listener);
  void			addMsgListener(IMsgListener * listener);
  void			addMsgErrorListener(IMsgErrorListener * listener);
  void			addUserInfoListener(IUserInfoListener * listener);

  static SizeTypeMap	initializeSizeTypeMap();
  static FunctorTypeMap initializeFunctorTypeMap();
  static ErrorMap	initializeErrorMap();

public:
  void			notifyCall(NET::CallInfo info);
  void			notifyConnect(void);
  void			notifyDisconnect(void);
  void			notifyError(QString error);
  void			notifyCallError(bool rep);
  void			notifyLogin(bool rep);
  void			notifyRegister(bool rep);
  void			notifyMsg(NET::MsgInfo info);
  void			notifyMsgError(bool rep);
  void			notifyUserInfo(NET::UserInfo info);

private:
  static SizeTypeMap				sizeTypeMap;
  static FunctorTypeMap				functorTypeMap;
  static ErrorMap				errorMap;
  TcpAsyncSocket				m_socket;
  NET::Type					typeNeeded;
  Timer						m_timer;
  char						buffer[4096];

  std::list<ICallListener *>			CallListenerList;
  std::list<IConnectListener *>			ConnectListenerList;
  std::list<IDisconnectListener *>		DisconnectListenerList;
  std::list<IErrorListener *>			ErrorListenerList;
  std::list<ICallErrorListener *>		CallErrorListenerList;
  std::list<ILoginListener *>			LoginListenerList;
  std::list<IRegisterListener *>		RegisterListenerList;
  std::list<IMsgListener *>			MsgListenerList;
  std::list<IMsgErrorListener *>		MsgErrorListenerList;
  std::list<IUserInfoListener *>		UserInfoListenerList;
};

#endif
