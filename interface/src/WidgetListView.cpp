#include	<iostream>
#include	"WidgetListView.hh"

WidgetListView::WidgetListView(QWidget *parent) : QListView(parent)
{
  this->_model = new QStandardItemModel();
  // Methode pour ajouter du contenu dans la liste
  this->_model->appendRow(new QStandardItem(QString("trololo")));
  this->_model->appendRow(new QStandardItem(QString("coucou")));
  this->setModel(this->_model);
}

void		WidgetListView::onData(NET::UserInfo info)
{
  std::cout << info.user << std::endl;
}

WidgetListView::~WidgetListView()
{
}
