#include	"WidgetTextView.hh"

<<<<<<< HEAD
WidgetTextView::WidgetTextView(const QString& user,
			       const QString& mate,
			       QWidget *parent) : QListWidget(parent)
{
  this->_user = user;
  this->_mate = mate;
  this->_userBrush.setColor(QColor(255, 0, 0));
  this->_mateBrush.setColor(QColor(0, 255, 0));
}

void		WidgetTextView::addMessageFromUser(const QString& msg)
{
  QListWidgetItem *item;

  item = new QListWidgetItem(msg);
  item->setBackground(this->_userBrush);
  this->addItem(item);
}

void		WidgetTextView::addMessageFromMate(const QString& msg)
{
  QListWidgetItem *item;

  item = new QListWidgetItem(msg);
  item->setBackground(this->_mateBrush);
  this->addItem(item);
=======
WidgetTextView::WidgetTextView(QWidget *parent) : QTextEdit(parent)
{
>>>>>>> 467e12c4204bc3f3fda64721866e77c9a9e5cf6c
}

WidgetTextView::~WidgetTextView() {}
