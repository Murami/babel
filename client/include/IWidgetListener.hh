#ifndef I_WIDGET_LISTENER_HH
#define I_WIDGET_LISTENER_HH

class IWidgetListener
{
public:
  virtual void onUserMsg(QString login, QString msg) = 0;
  virtual void onUserCall(QString login) = 0;
  virtual void onUserLogin(QString login, QString pass) = 0;
  virtual void onUserLogout(void) = 0;
  virtual void onUserRegister(QString login, QString pass) = 0;
  virtual void onUserAcceptCall(QString login) = 0;
  virtual void onUserDeclineCall(QString login) = 0;
  virtual void onUserHangout(QString login) = 0;
};

#endif
