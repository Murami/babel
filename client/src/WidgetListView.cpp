#include	<iostream>
#include	"WidgetListView.hh"
#include	"Protocol.hh"
#include	"User.hh"
#include	"ResourceManager.hpp"

WidgetListView::WidgetListView(QWidget *parent) : QListView(parent)
{
  this->_model = new QStandardItemModel();
  this->setModel(this->_model);
  connect(this, SIGNAL(clicked(const QModelIndex&)), this, SLOT(setSelectedContact(const QModelIndex&)));
  this->_selectedContactIndex = -1;
}

void		WidgetListView::setSelectedContact(const QModelIndex& index)
{
  if (index.row() < static_cast<int>(this->_contactList.size()))
    this->_selectedContactIndex = index.row();
}

int		WidgetListView::getSelectedContactIndex()
{
  return (this->_selectedContactIndex);
}

const std::string&	WidgetListView::getSelectedContactName()
{
  std::list<User*>::iterator it;
  int i = 0;
  for (it = this->_contactList.begin(); it != this->_contactList.end()
	 && i < this->_selectedContactIndex; it++)
    i++;
  return ((*it)->getName());
}

bool		WidgetListView::isSelectedContactConnected()
{
  std::list<User*>::iterator it;
  int i = 0;
  for (it = this->_contactList.begin(); it != this->_contactList.end()
	 && i < this->_selectedContactIndex; it++)
    i++;
  return ((*it)->isConnected());
}

void		WidgetListView::onUserInfo(NET::UserInfo info)
{
  bool		found = false;
  QList<QStandardItem*> list;

  for (std::list<User*>::iterator it = this->_contactList.begin();
       it != this->_contactList.end(); it++)
    {
      if ((*it)->getName() == info.user)
	{
	  (*it)->setConnected(info.status == NET::CONNECTED ? true : false);
	  found = true;
	  break;
	}
    }
  if (!found)
    this->_contactList.push_back(new User(info.user,
					  info.status == NET::CONNECTED ?
					  true : false));

  std::cout << "[ BEFORE SORT ]" << std::endl;
  for (std::list<User*>::iterator it = this->_contactList.begin(); it != this->_contactList.end(); it++)
    std::cout << (*it)->getName() << std::endl;

  this->_sortList();

  std::cout << "[ AFTER SORT ]" << std::endl;
  for (std::list<User*>::iterator it = this->_contactList.begin(); it != this->_contactList.end(); it++)
    std::cout << (*it)->getName() << std::endl;
  std::cout << std::endl;

  this->_model->clear();
  for (std::list<User*>::iterator it = this->_contactList.begin();
       it != this->_contactList.end(); it++)
    {
      NET::Status current = ((*it)->isConnected() ? NET::CONNECTED : NET::DISCONNECTED);
      QStandardItem *item = new QStandardItem(ResourceManager::getInstance()->getPellet(current),
					      QString((*it)->getName().c_str()));
      item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
      this->_model->appendRow(item);
    }
  this->_model->appendRow(list);
}

void		WidgetListView::_sortList()
{
  bool		flag = false;

  if (this->_contactList.size() >= 2)
    {
      while (!flag)
	{
	  flag = true;
	  std::list<User*>::iterator it = this->_contactList.begin();
	  std::list<User*>::iterator it2 = this->_contactList.begin();
	  it++;
	  for (; it != this->_contactList.end(); it++)
	    {
	      if (strcmp((*it)->getName().c_str(),
			 (*it2)->getName().c_str()) < 0)
		{
		  flag = false;
		  User *tmp;
		  tmp = (*it);
		  (*it) = (*it2);
		  (*it2) = tmp;
		  it2++;
		}
	    }
	}
    }
}

WidgetListView::~WidgetListView() {}
