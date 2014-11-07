#include	<QDesktopWidget>
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

  QDesktopWidget screen;

  this->move(screen.screenGeometry(0).width() / 2 - MainWindow::WIDTH / 2,
	     screen.screenGeometry(0).height() / 2 - MainWindow::HEIGHT / 2);

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
  this->_core.addUserInfoListener(this->_widgetListView);
  this->_core.addMsgListener(this);
}

void		MainWindow::setConnectedUserName(const QString& username)
{
  this->_connectedUser = username;
  this->_loggedUserLabel->setText(username);
  this->_userStatus->setPixmap(ResourceManager::getInstance()->getPellet(NET::CONNECTED).pixmap(20, 20));
  this->setWindowTitle(QString("Babel - ") + username);
}

void		MainWindow::onMsg(NET::MsgInfo info)
{
  ConversationWindow	*w;
  QString		*mate;

  mate = new QString(info.user);
  if (!this->_isConversationWindowOpen(info))
    {
      w = new ConversationWindow(this->_core, mate->toStdString());
      w->show();
      w->setUsername(*mate);
      w->onMsg(info);
      this->_conversationWindowList.push_back(std::string(info.user));
      this->_conversationWindows.push_back(w);
    }
}

bool		MainWindow::_isConversationWindowOpen(NET::MsgInfo info)
{
  for (std::list<std::string>::iterator it = this->_conversationWindowList.begin();
       it != this->_conversationWindowList.end(); it++)
    {
      if ((*it) == std::string(info.user))
	return (true);
    }
  return (false);
}

void		MainWindow::_connectWidgets()
{
  connect(this->_chatButton, SIGNAL(clicked()),
	  this, SLOT(createChatConversationWindow()));
  connect(this->_callButton, SIGNAL(clicked()),
	  this, SLOT(createAudioConversationWindow()));
  connect(this->_logoutButton, SIGNAL(clicked()),
	  this, SLOT(disconnect()));
}

void		MainWindow::disconnect()
{
  this->_core.onUserLogout();
  emit closeMainWindow();
}

void		MainWindow::createAudioConversationWindow()
{
  // AudioConversationWindow	*w;
  // QString			*mate;

  // if (this->_widgetListView->getSelectedContactIndex() != -1)
  //   {
  //     mate = new QString(this->_widgetListView->getSelectedContactName().c_str());
  //     if (this->_audioConversationWindowMap.find(mate) == this->_audioConversationWindowMap.end())
  // 	{
  // 	  w = new AudioConversationWindow(this->_core, mate->toStdString());
  // 	  w->setUsername(*mate);
  // 	  w->show();
  // 	  this->_audioConversationWindowMap[mate] = w;
  // 	}
  //   }
}

void		MainWindow::createChatConversationWindow()
{
  ConversationWindow	*w;
  QString		*mate;

  if (this->_widgetListView->getSelectedContactIndex() != -1)
    {
      mate = new QString(this->_widgetListView->getSelectedContactName().c_str());
      w = new ConversationWindow(this->_core, mate->toStdString());
      w->setUsername(*mate);
      w->show();
      this->_conversationWindowList.push_back(mate->toStdString());
      this->_conversationWindows.push_back(w);
    }
}

void		MainWindow::onDisconnect()
{
  //emit closeMainWindow();
  //this->close();
}

MainWindow::~MainWindow()
{
  std::cout << "DESTROYING" << std::endl;
  //this->_core.onDisconnect();
}
