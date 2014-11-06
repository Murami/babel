#include	<QMovie>
#include	<iostream>
#include	"ConversationWindow.hh"
#include	"WidgetButton.hh"
#include	"WidgetTextView.hh"

int		ConversationWindow::WIDTH = 640;
int		ConversationWindow::HEIGHT = 480;

ConversationWindow::ConversationWindow(const std::string& username, QWidget *parent) : QWidget(parent)
{
  QVBoxLayout		*mainLayout;
  QHBoxLayout		*layout;

  this->setFixedSize(ConversationWindow::WIDTH, ConversationWindow::HEIGHT);
  this->setWindowTitle(QString("Chat - ") + QString(username.c_str()));

  this->_sendMessageButton = new WidgetButton("Send");
  this->_quitButton = new WidgetButton("Close");
  layout = new QHBoxLayout();
  mainLayout = new QVBoxLayout();
  this->_messageTextView = new WidgetTextView();
  this->_messageEdit = new QLineEdit();

  this->_messageEdit->setFocus();
  this->_messageTextView->setEnabled(false);
  mainLayout->addWidget(this->_messageTextView);
  mainLayout->addWidget(this->_messageEdit);
  layout->addWidget(this->_sendMessageButton);
  layout->addWidget(this->_quitButton);
  mainLayout->addLayout(layout);
  this->setLayout(mainLayout);

  connect(this->_quitButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(this->_messageEdit, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
  connect(this->_sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

void		ConversationWindow::sendMessage()
{
  QString	str;

  std::cout << this->_messageEdit->text().toStdString() << std::endl;
  str = QString(this->_messageTextView->toPlainText());
  str += this->_messageEdit->text();
  str += QString("\n");
  this->_messageTextView->setText(str);
  this->_messageEdit->clear();
}

ConversationWindow::~ConversationWindow() {}
