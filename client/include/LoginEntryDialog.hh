#ifndef		__LOGINENTRYDIALOG_HH__
# define	__LOGINENTRYDIALOG_HH__

# include	<QDialog>
# include	<QLineEdit>
# include	<QVBoxLayout>
# include	<QHBoxLayout>
# include	"WidgetButton.hh"
# include	"ILoginListener.hh"

class		BabelCoreClient;

class		LoginEntryDialog : public QDialog, public ILoginListener
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

public:
  void		onData(bool);

public:
  LoginEntryDialog(BabelCoreClient&, QWidget *parent = 0);
  ~LoginEntryDialog();
};

#endif
