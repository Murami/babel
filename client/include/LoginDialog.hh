#ifndef		__LOGINDIALOG_HH__
# define	__LOGINDIALOG_HH__

# include	<QVBoxLayout>
# include	<QPushButton>
# include	<QDialog>
# include	"IErrorListener.hh"

class		MainWindow;
class		LoginEntryDialog;
class		RegisterEntryDialog;
class		BabelCoreClient;

class		LoginDialog : public QDialog, public IErrorListener
{
  Q_OBJECT

public:
  static int	WIDTH;
  static int	HEIGHT;

private:
  QVBoxLayout		*_layout;
  QPushButton		*_signInButton;
  QPushButton		*_logInButton;
  BabelCoreClient&	_core;
  LoginEntryDialog	*_loginDialog;
  RegisterEntryDialog	*_registerDialog;
  MainWindow		*_mainWindow;

public:
  void		onRegister(const QString&);
  void		onLogin(const QString&);

private slots:
  void		createSignInDialog();
  void		createLogInDialog();
  void		display();

public:
  void		onError(QString);

public:
  LoginDialog(BabelCoreClient&, QWidget *parent = 0);
  ~LoginDialog();
};

#endif		// __LOGINDIALOG_HH__
