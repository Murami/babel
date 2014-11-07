#include	<QScrollArea>
#include	"WidgetTextView.hh"

WidgetTextView::WidgetTextView(QWidget *parent) : QFrame(parent)
{
  this->_scrollArea = new QScrollArea(this);
}

WidgetTextView::~WidgetTextView() {}
