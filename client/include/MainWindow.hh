#ifndef		__MAINWINDOW_HH__
# define	__MAINWINDOW_HH__

# include	<QLabel>
# include	<QModelIndex>
# include	<QPushButton>
# include	<QHBoxLayout>
# include	<QVBoxLayout>
# include	<QMainWindow>

class		LoginDialog;
class		BabelCoreClient;
class		WidgetButton;
class		WidgetListView;
class		LoginDialog;

class		MainWindow : public QWidget
{
  Q_OBJECT

public:
  static int	WIDTH;
  static int	HEIGHT;

private:
  QHBoxLayout		*_mainLayout;
  QVBoxLayout		*_buttonLayout;
  QVBoxLayout		*_vLayout;
  QHBoxLayout		*_userLayout;
  QLabel		*_loggedUserLabel;
  QLabel		*_userStatus;
  WidgetButton		*_callButton;
  WidgetButton		*_logoutButton;
  WidgetButton		*_chatButton;
  LoginDialog		*_loginDialog;
  WidgetListView	*_widgetListView;
  BabelCoreClient&	_core;
  QString		_connectedUser;
  bool			_audioConversation;

public:
  void			setConnectedUserName(const QString&);

private slots:
  void			createAudioConversationWindow();
  void			createChatConversationWindow();

private:
  void			_connectWidgets();

public:
  MainWindow(BabelCoreClient&, QWidget *parent = 0);
  ~MainWindow();
};

#endif		// MainWindow
