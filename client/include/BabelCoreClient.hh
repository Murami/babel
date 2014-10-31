#ifndef BABEL_CORE_CLIENT_HH
#define BABEL_CORE_CLIENT_HH

#include <list>

#include "IAsyncSocketListener.hh"
#include "ICoreListener.hh"
#include "IWidgetListener.hh"
#include "QTcpAsyncSocket.hh"

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

  void addUserInfoListener(ICoreListener * listener);
  void addCallListener(ICoreListener * listener);
  void addHangoutListener(ICoreListener * listener);
  void addMsgListener(ICoreListener * listener);
  void addConnectListener(ICoreListener * listener);
  void addDisconnectListener(ICoreListener * listener);
  void addErrorListener(ICoreListener * listener);

private:
  void notifyCall();
  void notifyMsg();
  void notifyHangout();
  void notifyUserInfo();
  void notifyConnect();
  void notifyDisconnect();
  void notifyError();

private:
  QTcpAsyncSocket m_socket;
  std::list<ICoreListener *> UserInfoListenerList;
  std::list<ICoreListener *> CallListenerList;
  std::list<ICoreListener *> HangoutListenerList;
  std::list<ICoreListener *> MsgListenerList;
  std::list<ICoreListener *> ConnectListenerList;
  std::list<ICoreListener *> DisconnectListenerList;
  std::list<ICoreListener *> ErrorListenerList;
};

#endif
