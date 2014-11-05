#include	<iostream>
#include	<QLineEdit>

#include	"WidgetListView.hh"
#include	"LoginDialog.hh"
#include	"MainWindow.hh"

#include	"ConversationWindow.hh"
#include	"AddNewContactDialog.hh"
#include	"WidgetButton.hh"

#include	"BabelCoreClient.hh"

int		MainWindow::WIDTH = 800;
int		MainWindow::HEIGHT = 600;

MainWindow::MainWindow(BabelCoreClient& core, QWidget *parent) : QWidget(parent), _core(core)
{
  this->_widgetListView = new WidgetListView(this);
  this->_callButton = new WidgetButton("Call", this);
  this->_mainLayout = new QHBoxLayout(this);
  this->_buttonLayout = new QVBoxLayout();
  this->_addContactButton = new WidgetButton("Add", this);
  this->_vLayout = new QVBoxLayout();
  this->_loggedUserLabel = new QLabel("Disconnected", this);
  this->_userLayout = new QHBoxLayout();
  this->_userStatus = new QLabel(this);
//this->_connectButton = new WidgetButton("Connect", this);

  this->_loginDialog = static_cast<LoginDialog*>(parent);
  this->_userLayout->setAlignment(Qt::AlignLeft);
  this->_userStatus->setPixmap(ResourceManager::getInstance()->getPellet(NET::DISCONNECTED).pixmap(20, 20));
  this->_userLayout->addWidget(this->_userStatus);
  this->_userLayout->addWidget(this->_loggedUserLabel);
  this->_vLayout->addLayout(this->_userLayout);
  this->_vLayout->addWidget(this->_widgetListView);
  this->_callButton->setFixedSize(200, 50);
  this->setFixedSize(MainWindow::WIDTH, MainWindow::HEIGHT);
  this->setWindowTitle("Babel");
  this->_addContactButton->setFixedSize(200, 50);
//this->_connectButton->setFixedSize(200, 50);
//this->_buttonLayout->addWidget(this->_connectButton);
  this->_buttonLayout->addWidget(this->_callButton);
  this->_buttonLayout->setAlignment(this->_callButton, Qt::AlignHCenter);
  this->_buttonLayout->addWidget(this->_addContactButton);
  this->_buttonLayout->setAlignment(this->_addContactButton, Qt::AlignHCenter);
  this->_mainLayout->addLayout(this->_vLayout);
  this->_mainLayout->addLayout(this->_buttonLayout);
  this->_connectWidgets();
}

void		MainWindow::setConnectedUserName(const QString& username)
{
  this->_connectedUser = username;
  this->_loggedUserLabel->setText(username);
  this->_userStatus->setPixmap(ResourceManager::getInstance()->getPellet(NET::CONNECTED).pixmap(20, 20));
}

void		MainWindow::_connectWidgets()
{
  connect(this->_callButton, SIGNAL(clicked()),
	  this, SLOT(createConversationWindow()));
  connect(this->_addContactButton, SIGNAL(clicked()),
	  this, SLOT(createNewContactDialog()));
  // connect(this->_connectButton, SIGNAL(clicked()),
  // 	  this, SLOT(createLoginDialog()));
}

void		MainWindow::createLoginDialog()
{
  LoginDialog	*dialog;

  dialog = new LoginDialog(this->_core, this);
  dialog->show();
  this->close();
}

void		MainWindow::createConversationWindow()
{
  ConversationWindow	*w;

  if (this->_widgetListView->getSelectedContactIndex() != -1)
    {
      w = new ConversationWindow();
      w->show();
    }
}

void		MainWindow::createNewContactDialog()
{
  AddNewContactDialog *dialog;

  dialog = new AddNewContactDialog(this);
  dialog->show();
}

MainWindow::~MainWindow() {}
