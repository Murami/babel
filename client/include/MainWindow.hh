#ifndef		__MAINWINDOW_HH__
# define	__MAINWINDOW_HH__

# include	<QLabel>
# include	<QModelIndex>
# include	<QPushButton>
# include	<QHBoxLayout>
# include	<QVBoxLayout>
# include	<QMainWindow>

class		BabelCoreClient;
class		WidgetButton;
class		WidgetListView;
class		LoginDialog;

class		MainWindow : public QWidget
{
  Q_OBJECT

private:
  QHBoxLayout		*_mainLayout;
  QVBoxLayout		*_buttonLayout;
  QVBoxLayout		*_vLayout;
  QHBoxLayout		*_userLayout;
  QLabel		*_loggedUserLabel;
  QLabel		*_userStatus;
  WidgetButton		*_callButton;
  WidgetButton		*_addContactButton;
  WidgetButton		*_connectButton;
  LoginDialog		*_loginDialog;
  WidgetListView	*_widgetListView;
  BabelCoreClient&	_core;

public:
  static int	WIDTH;
  static int	HEIGHT;

private slots:
  void			createNewContactDialog();
  void			createConversationWindow();
  void			createLoginDialog();

private:
  void			_connectWidgets();

public:
  MainWindow(BabelCoreClient&, QWidget *parent = 0);
  ~MainWindow();
};

#endif		// MainWindow
