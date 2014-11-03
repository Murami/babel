#ifndef		__CONTACTLISTVIEW_HH__
# define	__CONTACTLISTVIEW_HH__

# include	<QString>
# include	<QList>
# include	<QStandardItemModel>
# include	<QListView>
# include	"IUserInfoListener.hh"

class		WidgetListView : public QListView, public IUserInfoListener
{
private:
  QStandardItemModel	*_model;
  QList<QStandardItem*>	_contactList;

public:
  virtual void	onData(NET::UserInfo);

public:
  WidgetListView(QWidget *parent = 0);
  ~WidgetListView();
};

#endif
