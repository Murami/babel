#include	<iostream>
#include	<QLineEdit>

#include	"WidgetListView.hh"
#include	"LoginDialog.hh"
#include	"MainWindow.hh"

#include	"AudioConversationWindow.hh"
#include	"ConversationWindow.hh"
#include	"WidgetButton.hh"

#include	"BabelCoreClient.hh"

int		MainWindow::WIDTH = 640;
int		MainWindow::HEIGHT = 480;

MainWindow::MainWindow(BabelCoreClient& core, QWidget *parent) : QWidget(parent), _core(core)
{
  this->_chatButton = new WidgetButton("Chat", this);
  this->_logoutButton = new WidgetButton("Logout", this);
  this->_widgetListView = new WidgetListView(this);
  this->_callButton = new WidgetButton("Call", this);
  this->_mainLayout = new QHBoxLayout(this);
  this->_buttonLayout = new QVBoxLayout();
  this->_vLayout = new QVBoxLayout();
  this->_loggedUserLabel = new QLabel("Disconnected", this);
  this->_userLayout = new QHBoxLayout();
  this->_userStatus = new QLabel(this);

  this->_loginDialog = static_cast<LoginDialog*>(parent);
  this->_userLayout->setAlignment(Qt::AlignLeft);
  this->_userStatus->setPixmap(ResourceManager::getInstance()->getPellet(NET::DISCONNECTED).pixmap(20, 20));
  this->_userLayout->addWidget(this->_userStatus);
  this->_userLayout->addWidget(this->_loggedUserLabel);
  this->_vLayout->addLayout(this->_userLayout);
  this->_vLayout->addWidget(this->_widgetListView);

  this->_chatButton->setFixedSize(200, 50);
  this->_logoutButton->setFixedSize(200, 50);
  this->_callButton->setFixedSize(200, 50);

  this->setFixedSize(MainWindow::WIDTH, MainWindow::HEIGHT);
  this->setWindowTitle("Babel");

  this->_buttonLayout->addWidget(this->_logoutButton);
  this->_buttonLayout->addWidget(this->_chatButton);
  this->_buttonLayout->addWidget(this->_callButton);
  this->_buttonLayout->setAlignment(this->_callButton, Qt::AlignHCenter);
  this->_buttonLayout->setAlignment(this->_chatButton, Qt::AlignHCenter);
  this->_buttonLayout->setAlignment(this->_logoutButton, Qt::AlignHCenter);

  this->_mainLayout->addLayout(this->_vLayout);
  this->_mainLayout->addLayout(this->_buttonLayout);
  this->_connectWidgets();
  this->_audioConversation = false;
}

void		MainWindow::setConnectedUserName(const QString& username)
{
  this->_connectedUser = username;
  this->_loggedUserLabel->setText(username);
  this->_userStatus->setPixmap(ResourceManager::getInstance()->getPellet(NET::CONNECTED).pixmap(20, 20));
}

void		MainWindow::_connectWidgets()
{
  connect(this->_chatButton, SIGNAL(clicked()),
	  this, SLOT(createChatConversationWindow()));
  connect(this->_callButton, SIGNAL(clicked()),
	  this, SLOT(createAudioConversationWindow()));
}

void		MainWindow::createAudioConversationWindow()
{
  AudioConversationWindow	*w;

  if (!this->_audioConversation)
    {
      this->_audioConversation = true;
      w = new AudioConversationWindow(this);
      w->show();
    }
}

void		MainWindow::createChatConversationWindow()
{
  ConversationWindow	*w;

  if (this->_widgetListView->getSelectedContactIndex() != -1)
    {
      w = new ConversationWindow(this);
      w->show();
    }
}

MainWindow::~MainWindow() {}
