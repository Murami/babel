#include	"WidgetTextView.hh"

WidgetTextView::WidgetTextView(const QString& user,
			       const QString& mate,
			       QWidget *parent) : QListWidget(parent)
{
  this->_user = user;
  this->_mate = mate;
  this->_userBrush.setColor(QColor(53, 249, 144));
  this->_mateBrush.setColor(QColor(57, 165, 186));
}

void		WidgetTextView::addMessageFromUser(const QString& msg)
{
  QListWidgetItem *item;

  item = new QListWidgetItem(msg);
  this->_userBrush.setStyle(Qt::SolidPattern);
  item->setBackground(this->_userBrush);
  this->addItem(item);
  this->scrollToBottom();
}

void		WidgetTextView::addMessageFromMate(const QString& msg)
{
  QListWidgetItem *item;

  item = new QListWidgetItem(msg);
  this->_mateBrush.setStyle(Qt::SolidPattern);
  item->setBackground(this->_mateBrush);
  this->addItem(item);
  this->scrollToBottom();
}

WidgetTextView::~WidgetTextView() {}
