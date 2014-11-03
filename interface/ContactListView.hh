#ifndef		__CONTACTLISTVIEW_HH__
# define	__CONTACTLISTVIEW_HH__

# include	<QListView>

class		ContactListController;

// Faire heriter la classe d'une interface Updatable pour la mettre a jour
class		ContactListView : public QListView
{
private:
  ContactListController	*_controller;

public:
  ContactListView(QWidget *parent = 0);
  ~ContactListView();
};

#endif
