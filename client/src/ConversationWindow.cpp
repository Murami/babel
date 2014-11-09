#include	<QDesktopWidget>
#include	<QMovie>
#include	<iostream>
#include	"ConversationWindow.hh"
#include	"WidgetButton.hh"
#include	"WidgetTextView.hh"
#include	"BabelCoreClient.hh"

int		ConversationWindow::WIDTH = 640;
int		ConversationWindow::HEIGHT = 480;

ConversationWindow::ConversationWindow(BabelCoreClient& core,
				       const std::string& user,
				       const std::string& mate,
				       QWidget *parent) : QWidget(parent), _core(core)
{
  QVBoxLayout		*mainLayout;
  QHBoxLayout		*layout;
  QDesktopWidget	screen;

  this->_username = QString(user.c_str());
  this->_core.addMsgErrorListener(this);
  this->_core.addMsgListener(this);
  this->move(screen.screenGeometry(0).width() / 2 - ConversationWindow::WIDTH / 2,
	     screen.screenGeometry(0).height() / 2 - ConversationWindow::HEIGHT / 2);
  this->setFixedSize(ConversationWindow::WIDTH, ConversationWindow::HEIGHT);
  this->setWindowTitle(QString("Chat - ") + QString(mate.c_str()));
  this->_connectedMate = QString(mate.c_str());
  this->_sendMessageButton = new WidgetButton("Send");
  this->_quitButton = new WidgetButton("Close");
  layout = new QHBoxLayout();
  mainLayout = new QVBoxLayout();
  this->_messageTextView = new WidgetTextView(this->_username, this->_connectedMate);
  this->_messageEdit = new QLineEdit();
  this->_messageEdit->setFocus();
  mainLayout->addWidget(this->_messageTextView);
  mainLayout->addWidget(this->_messageEdit);
  layout->addWidget(this->_sendMessageButton);
  layout->addWidget(this->_quitButton);
  mainLayout->addLayout(layout);
  this->setLayout(mainLayout);
  connect(this->_quitButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
  connect(this->_messageEdit, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
  connect(this->_sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

void		ConversationWindow::closeWindow()
{
  emit closed(this);
  this->close();
}

void		ConversationWindow::closeEvent(QCloseEvent *)
{
  emit closed(this);
  this->close();
}

void		ConversationWindow::setUsername(const QString& username)
{
  this->_username = username;
}

void		ConversationWindow::onMsgError(bool lol)
{
  if (lol)
    {
      std::cerr << "[ CONVERSATION ]: Received an error." << std::endl;
    }
  else
    {
      std::cerr << "[ CONVERSATION ]: Error while attempting to send message." << std::endl;
    }
}

void		ConversationWindow::onMsg(NET::MsgInfo info)
{
  this->_messageTextView->addMessageFromMate(QString(info.msg));
}

void		ConversationWindow::sendMessage()
{
  QString	msg;

  msg = this->_messageEdit->text();
  if (msg.length())
    {
      this->_messageTextView->addMessageFromUser(this->_messageEdit->text());
      this->_messageEdit->clear();
      this->_core.onUserMsg(this->_connectedMate, msg);
    }
}

ConversationWindow::~ConversationWindow()
{
  this->_core.deleteMsgErrorListener(this);
  this->_core.deleteMsgListener(this);
}
