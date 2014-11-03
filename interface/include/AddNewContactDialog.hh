#ifndef		__ADDNEWCONTACTDIALOG_HH__
# define	__ADDNEWCONTACTDIALOG_HH__

# include	<QHBoxLayout>
# include	<QVBoxLayout>
# include	<QPalette>
# include	<QDialog>
# include	<QLineEdit>
# include	"WidgetButton.hh"

class		AddNewContactDialog : public QDialog
{
  Q_OBJECT

private:
  QLineEdit	*_tagEdit;
  WidgetButton	*_addButton;
  WidgetButton	*_cancelButton;
  QVBoxLayout	*_vlayout;
  QHBoxLayout	*_hlayout;
  QPalette	_palette;

private slots:
  void		sendRequest();

public:
  AddNewContactDialog(QWidget *parent = 0);
  ~AddNewContactDialog();
};

#endif
