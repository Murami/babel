#ifndef		__CONTACTLISTVIEW_HH__
# define	__CONTACTLISTVIEW_HH__

# include	<list>
# include	<QString>
# include	<QList>
# include	<QStandardItemModel>
# include	<QListView>
# include	"IUserInfoListener.hh"

class		User;

class		WidgetListView : public QListView, public IUserInfoListener
{
  Q_OBJECT

private:
  QStandardItemModel	*_model;
  std::list<User*>	_contactList;
  int			_selectedContactIndex;

private:
  void		_sortList();

public:
  int			getSelectedContactIndex();
  const std::string&	getSelectedContactName();
  bool			isSelectedContactConnected();

private slots:
  void		setSelectedContact(const QModelIndex&);

public:
  virtual void	onData(NET::UserInfo);

public:
  WidgetListView(QWidget *parent = 0);
  ~WidgetListView();
};

#endif
