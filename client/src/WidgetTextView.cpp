#include	"WidgetTextView.hh"

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
  this->_userBrush.setStyle(Qt::SolidPattern);
  item->setBackground(this->_userBrush);
  this->addItem(item);
}

void		WidgetTextView::addMessageFromMate(const QString& msg)
{
  QListWidgetItem *item;

  item = new QListWidgetItem(msg);
  this->_mateBrush.setStyle(Qt::SolidPattern);
  item->setBackground(this->_mateBrush);
  this->addItem(item);
}

WidgetTextView::~WidgetTextView() {}
