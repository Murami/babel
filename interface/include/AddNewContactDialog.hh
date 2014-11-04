#ifndef		__ADDNEWCONTACTDIALOG_HH__
# define	__ADDNEWCONTACTDIALOG_HH__

# include	<QHBoxLayout>
# include	<QVBoxLayout>
# include	<QDialog>
# include	<QLineEdit>
# include	"WidgetButton.hh"
# include	"IWidgetListener.hh"

class		AddNewContactDialog : public QDialog
{
  Q_OBJECT

private:
  QLineEdit		*_tagEdit;
  WidgetButton		*_addButton;
  WidgetButton		*_cancelButton;
  QVBoxLayout		*_vlayout;
  QHBoxLayout		*_hlayout;
  IWidgetListener	*_widgetListener;

private slots:
  void		sendRequest();

public:
  AddNewContactDialog(QWidget *parent = 0);
  ~AddNewContactDialog();
};

#endif
