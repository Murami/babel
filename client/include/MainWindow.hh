#ifndef		__MAINWINDOW_HH__
# define	__MAINWINDOW_HH__

# include	<list>
# include	<QLabel>
# include	<QModelIndex>
# include	<QPushButton>
# include	<QHBoxLayout>
# include	<QVBoxLayout>
# include	<QMainWindow>
# include	"IMsgListener.hh"
# include	"IDisconnectListener.hh"
# include	"ConversationWindow.hh"
# include	"AudioConversationWindow.hh"

class		LoginDialog;
class		BabelCoreClient;
class		WidgetButton;
class		WidgetListView;
class		LoginDialog;

class		MainWindow : public QWidget,
			     public IMsgListener,
			     public IDisconnectListener
{
  Q_OBJECT

public:
  static int	WIDTH;
  static int	HEIGHT;

private:
  QHBoxLayout				*_mainLayout;
  QVBoxLayout				*_buttonLayout;
  QVBoxLayout				*_vLayout;
  QHBoxLayout				*_userLayout;
  QLabel				*_loggedUserLabel;
  QLabel				*_userStatus;
  WidgetButton				*_callButton;
  WidgetButton				*_logoutButton;
  WidgetButton				*_chatButton;
  LoginDialog				*_loginDialog;
  WidgetListView			*_widgetListView;
  BabelCoreClient&			_core;
  QString				_connectedUser;
  std::list<std::string>		_audioConversationWindowList;
  std::list<std::string>		_conversationWindowList;
  std::list<ConversationWindow*>	_conversationWindows;

public:
  void			setConnectedUserName(const QString&);

public:
  virtual void		onMsg(NET::MsgInfo);
  virtual void		onDisconnect(void);

signals:
  void			closeMainWindow();

private slots:
  void			createAudioConversationWindow();
  void			createChatConversationWindow();
  void			disconnect();

private:
  void			_connectWidgets();
  bool			_isConversationWindowOpen(NET::MsgInfo);
  bool			_isAudioConversationWindowOpen();

public:
  MainWindow(BabelCoreClient&, QWidget *parent = 0);
  ~MainWindow();
};

#endif		// MainWindow
