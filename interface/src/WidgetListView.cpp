#include	<iostream>
#include	"WidgetListView.hh"

WidgetListView::WidgetListView(QWidget *parent) : QListView(parent)
{
}

void		WidgetListView::onData(NET::UserInfo info)
{
  std::cout << info.user << std::endl;
}

WidgetListView::~WidgetListView()
{
}
