#ifndef		__LOGINDIALOG_HH__
# define	__LOGINDIALOG_HH__

# include	<QVBoxLayout>
# include	<QPushButton>
# include	<QDialog>

class		LoginDialog : public QDialog
{
  Q_OBJECT

public:
  static int	WIDTH;
  static int	HEIGHT;

private:
  QVBoxLayout	*_layout;
  QPushButton	*_signInButton;
  QPushButton	*_logInButton;

private slots:
  void		createSignInDialog();
  void		createLogInDialog();

public:
  LoginDialog(QWidget *parent);
  ~LoginDialog();
};

#endif		// __LOGINDIALOG_HH__
