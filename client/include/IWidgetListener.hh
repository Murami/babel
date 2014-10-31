#ifndef I_WIDGET_LISTENER_HH
#define I_WIDGET_LISTENER_HH

class IWidgetListener
{
public:
  virtual void onUserMsg() = 0;
  virtual void onUserCall() = 0;
  virtual void onUserLogin() = 0;
  virtual void onUserLogout() = 0;
  virtual void onUserRegister() = 0;
  virtual void onUserAcceptCall() = 0;
  virtual void onUserDeclineCall() = 0;
};

#endif
