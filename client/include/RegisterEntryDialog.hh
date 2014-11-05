#ifndef		__REGISTERENTRYDIALOG_HH__
# define	__REGISTERENTRYDIALOG_HH__

# include	<QDialog>
# include	<QVBoxLayout>
# include	<QHBoxLayout>
# include	<QLineEdit>
# include	"WidgetButton.hh"
# include	"IRegisterListener.hh"

class		BabelCoreClient;

class		RegisterEntryDialog : public QDialog, public IRegisterListener
{
  Q_OBJECT

private:
  BabelCoreClient&	_core;
  QVBoxLayout		*_vLayout;
  QHBoxLayout		*_hLayout;
  WidgetButton		*_signInButton;
  WidgetButton		*_cancelButton;
  QLineEdit		*_pseudoEdit;
  QLineEdit		*_passwordEdit1;
  QLineEdit		*_passwordEdit2;

public:
  void		onData(bool);

public:
  RegisterEntryDialog(BabelCoreClient&, QWidget *parent = 0);
  ~RegisterEntryDialog();
};

#endif