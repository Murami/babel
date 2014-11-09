#include	<iostream>
#include	<QPen>
#include	<QColor>
#include	<QFont>
#include	<QPainter>
#include	"Protocol.hh"
#include	"WidgetButton.hh"

WidgetButton::WidgetButton(const QString& text, QWidget *parent) : QPushButton(parent)
{
  this->_text = text;
  this->_image = ResourceManager::getInstance()->getNormalButtonPixmap();
  this->setFixedSize(100, 50);
}

void		WidgetButton::paintEvent(QPaintEvent *event)
{
  QPainter	painter(this);

  painter.setFont(QFont("Sans", 15));
  painter.setPen(QPen(QColor(255, 255, 255)));
  this->_drawRect = event->rect();
  painter.drawPixmap(event->rect(), *this->_image);
  painter.drawText(event->rect(), Qt::AlignCenter, this->_text);
}

void			WidgetButton::onCall(NET::CallInfo)
{
}

void			WidgetButton::enterEvent(QEvent *)
{
  this->_image = ResourceManager::getInstance()->getHoveredButtonPixmap();
}

void			WidgetButton::leaveEvent(QEvent *)
{
  this->_image = ResourceManager::getInstance()->getNormalButtonPixmap();
}

void			WidgetButton::mousePressEvent(QMouseEvent *)
{
  this->_image = ResourceManager::getInstance()->getPressedButtonPixmap();
  this->repaint();
}

void			WidgetButton::mouseReleaseEvent(QMouseEvent *)
{
  this->_image = ResourceManager::getInstance()->getHoveredButtonPixmap();
  this->repaint();
  this->clicked();
}

WidgetButton::~WidgetButton()
{
}
