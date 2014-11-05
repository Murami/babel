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
  this->_register = false;
  this->_mainWindow = new MainWindow(core);

  this->_loginDialog = new LoginEntryDialog(core, this);

  this->_registerDialog = new RegisterEntryDialog(core, this);

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

void		LoginDialog::onLogin(const QString& username)
{
  std::cout << "YAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << username.toStdString() << std::endl;
  this->_mainWindow->setConnectedUserName(username);
  this->_mainWindow->show();
  this->hide();
}

void		LoginDialog::onRegister(const QString& username)
{
  std::cout << "YAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << username.toStdString() << std::endl;
  this->_register = true;
  this->_mainWindow->setConnectedUserName(username);
  this->_mainWindow->show();
  this->hide();
}

void		LoginDialog::createLogInDialog()
{
  this->_core.addLoginListener(this->_loginDialog);
  this->_loginDialog->show();
}

void		LoginDialog::createSignInDialog()
{
  this->_core.addRegisterListener(this->_registerDialog);
  this->_registerDialog->show();
}

LoginDialog::~LoginDialog() {}
