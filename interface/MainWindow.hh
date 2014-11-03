#ifndef		__MAINWINDOW_HH__
# define	__MAINWINDOW_HH__

# include	<QPushButton>
# include	<QHBoxLayout>
# include	<QVBoxLayout>
# include	<QMainWindow>

class		ContactListModel;
class		ContactListController;
class		ContactListView;
class		LoginDialog;

// Faire heriter cette classe de IBabelActionListener
class		MainWindow : public QWidget
{
  Q_OBJECT

private:
  QHBoxLayout		*_mainLayout;
  QVBoxLayout		*_layout;
  QPushButton		*_callButton;
  QPushButton		*_addContactButton;
  LoginDialog		*_loginDialog;
  ContactListView	*_contactListView;

public:
  static int	WIDTH;
  static int	HEIGHT;

private slots:
  void			createNewContactDialog();

private:
  void			_connectButtons();

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
};

#endif		// MainWindow
