#include	<QDesktopWidget>
#include	<iostream>
#include	<QLineEdit>

#include	"WidgetListView.hh"
#include	"LoginDialog.hh"
#include	"MainWindow.hh"

#include	"AudioCallConfirmationDialog.hh"
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

  this->_core.addDisconnectListener(this);
  this->_core.addUserInfoListener(this->_widgetListView);
  this->_core.addMsgListener(this);
  this->_core.addCallListener(this);
  this->_audioWindow = NULL;
}

void		MainWindow::deleteAudioWindow()
{
  this->_audioWindow->close();
  delete this->_audioWindow;
  this->_audioWindow = NULL;
}

void		MainWindow::setConnectedUserName(const QString& username)
{
  this->_connectedUser = username;
  this->_loggedUserLabel->setText(username);
  this->_userStatus->setPixmap(ResourceManager::getInstance()->getPellet(NET::CONNECTED).pixmap(20, 20));
  this->setWindowTitle(QString("Babel - ") + username);
}

void		MainWindow::deleteConversationWindow(ConversationWindow *w)
{
  std::list<ConversationWindow*>::iterator it;
  std::list<std::string>::iterator name = this->_conversationWindowList.begin();
  for (it = this->_conversationWindows.begin();
       it != this->_conversationWindows.end(); it++)
    {
      if ((*it) == w)
	{
	  this->_conversationWindowList.erase(name);
	  this->_conversationWindows.erase(it);
	  break;
	}
      name++;
    }
}

void		MainWindow::closeEvent(QCloseEvent *)
{
  this->_core.onUserLogout();
  emit closeMainWindow();
}

void		MainWindow::openAudioConversationWindow(const QString& caller)
{
  this->_audioWindow = new AudioConversationWindow(this->_core,
						   caller.toStdString(),
						   this->_connectedUser.toStdString());
  this->_audioWindow->show();
  connect(this->_audioWindow, SIGNAL(closed()),
	  this, SLOT(deleteAudioWindow()));
}

void		MainWindow::onCall(NET::CallInfo info)
{
  if (this->_audioWindow == NULL)
    {
      QString mate(info.user);
      AudioCallConfirmationDialog *dialog = new AudioCallConfirmationDialog(this->_core,
      									    mate, this);
      dialog->show();
    }
}

void		MainWindow::onMsg(NET::MsgInfo info)
{
  ConversationWindow	*w;
  QString		*mate;

  mate = new QString(info.user);
  if (!this->_isConversationWindowOpen(QString(info.user)))
    {
      w = new ConversationWindow(this->_core, this->_connectedUser.toStdString(),
				 mate->toStdString());
      w->show();
      w->setUsername(this->_connectedUser);
      w->onMsg(info);
      connect(w, SIGNAL(closed(ConversationWindow*)),
	      this, SLOT(deleteConversationWindow(ConversationWindow*)));
      this->_conversationWindowList.push_back(std::string(info.user));
      this->_conversationWindows.push_back(w);
    }
}

bool		MainWindow::_isConversationWindowOpen(const QString& username)
{
  for (std::list<std::string>::iterator it = this->_conversationWindowList.begin();
       it != this->_conversationWindowList.end(); it++)
    {
      if ((*it) == username.toStdString())
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
  for (std::list<ConversationWindow*>::iterator it = this->_conversationWindows.begin();
       it != this->_conversationWindows.end(); it++)
    (*it)->close();
  if (this->_audioWindow != NULL)
    this->_audioWindow->close();
  emit closeMainWindow();
  this->close();
}

void		MainWindow::createAudioConversationWindow()
{
  QString		*mate;

  if (this->_widgetListView->getSelectedContactIndex() != -1 &&
      this->_widgetListView->isSelectedContactConnected() &&
      this->_audioWindow == NULL)
    {
      mate = new QString(this->_widgetListView->getSelectedContactName().c_str());
      this->_audioWindow = new AudioConversationWindow(this->_core,
						       mate->toStdString(),
						       this->_connectedUser.toStdString());
      this->_audioWindow->show();
      connect(this->_audioWindow, SIGNAL(closed()),
	      this, SLOT(deleteAudioWindow()));
    }
}

void		MainWindow::createChatConversationWindow()
{
  ConversationWindow	*w;
  QString		*mate;

  if (this->_widgetListView->getSelectedContactIndex() != -1 &&
      this->_widgetListView->isSelectedContactConnected() &&
      !this->_isConversationWindowOpen(QString(this->_widgetListView->getSelectedContactName().c_str())))
    {
      mate = new QString(this->_widgetListView->getSelectedContactName().c_str());
      w = new ConversationWindow(this->_core, this->_connectedUser.toStdString(),
				 mate->toStdString());
      w->setUsername(this->_connectedUser);
      w->show();
      connect(w, SIGNAL(closed(ConversationWindow*)),
	      this, SLOT(deleteConversationWindow(ConversationWindow*)));
      this->_conversationWindowList.push_back(mate->toStdString());
      this->_conversationWindows.push_back(w);
    }
}

void		MainWindow::onDisconnect()
{
  disconnect();
}

MainWindow::~MainWindow()
{
  this->_core.deleteDisconnectListener(this);
  this->_core.deleteUserInfoListener(this->_widgetListView);
  this->_core.deleteMsgListener(this);
  this->_core.deleteCallListener(this);
}
