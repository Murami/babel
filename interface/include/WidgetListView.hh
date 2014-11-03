#ifndef		__CONTACTLISTVIEW_HH__
# define	__CONTACTLISTVIEW_HH__

# include	<QListView>
# include	"IUserInfoListener.hh"

class		WidgetListView : public QListView, public IUserInfoListener
{
public:
  virtual void	onData(NET::UserInfo);

public:
  WidgetListView(QWidget *parent = 0);
  ~WidgetListView();
};

#endif
