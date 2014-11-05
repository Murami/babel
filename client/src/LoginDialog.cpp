#include	<QLineEdit>
#include	<iostream>
#include	"WidgetButton.hh"
#include	"LoginDialog.hh"
#include	"LoginEntryDialog.hh"
#include	"RegisterEntryDialog.hh"
#include	"BabelCoreClient.hh"
#include	"MainWindow.hh"

int		LoginDialog::WIDTH = 300;
int		LoginDialog::HEIGHT = 200;

LoginDialog::LoginDialog(BabelCoreClient& core, QWidget *parent) : QDialog(parent), _core(core)
{
  this->_mainWindow = new MainWindow(core, this);
  this->_loginDialog = new LoginEntryDialog(this->_core, this);
  this->_registerDialog = new RegisterEntryDialog(this->_core, this);
  this->setWindowTitle("Logging in");
  this->setFixedSize(LoginDialog::WIDTH, LoginDialog::HEIGHT);
  this->_layout = new QVBoxLayout();
  this->_signInButton = new WidgetButton("Sign In", this);
  this->_logInButton = new WidgetButton("Log In", this);
  this->_layout->addWidget(this->_logInButton);
  this->_layout->setAlignment(this->_logInButton, Qt::AlignHCenter);
  this->_layout->addWidget(this->_signInButton);
  this->_layout->setAlignment(this->_signInButton, Qt::AlignHCenter);
  this->setLayout(this->_layout);
  connect(this->_signInButton, SIGNAL(clicked()), this, SLOT(createSignInDialog()));
  connect(this->_logInButton, SIGNAL(clicked()), this, SLOT(createLogInDialog()));
}

void		LoginDialog::createLogInDialog()
{
  this->_loginDialog->show();
}

void		LoginDialog::createSignInDialog()
{
  this->_registerDialog->show();
}

LoginDialog::~LoginDialog() {}
