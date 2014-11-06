#ifndef		__LOGINENTRYDIALOG_HH__
# define	__LOGINENTRYDIALOG_HH__

# include	<QString>
# include	<QDialog>
# include	<QLineEdit>
# include	<QVBoxLayout>
# include	<QHBoxLayout>
# include	"WidgetButton.hh"
# include	"ILoginListener.hh"
# include	"IErrorListener.hh"

class		LoginDialog;
class		BabelCoreClient;

class		LoginEntryDialog : public QDialog,
				   public ILoginListener,
				   public IErrorListener
{
  Q_OBJECT

private:
  BabelCoreClient&	_core;
  QVBoxLayout		*_vLayout;
  QHBoxLayout		*_hLayout;
  WidgetButton		*_logInButton;
  WidgetButton		*_cancelButton;
  QLineEdit		*_pseudoEdit;
  QLineEdit		*_passwordEdit;
  QDialog		*_dialog;
  LoginDialog		*_parent;
  QString		_user;

private:
  void		_createErrorBox(const QString&, const QString&);

public:
  void		onLogin(bool);
  virtual	void	onError(QString);

private slots:
  void		sendData();

public:
  LoginEntryDialog(BabelCoreClient&, QWidget *parent = 0);
  ~LoginEntryDialog();
};

#endif
