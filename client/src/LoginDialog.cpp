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
  this->_initialize();
}

void		LoginDialog::_initialize()
{
  this->_mainWindow = NULL;
  this->_loginDialog = NULL;
  this->_registerDialog = NULL;

  connect(this->_signInButton, SIGNAL(clicked()), this, SLOT(createSignInDialog()));
  connect(this->_logInButton, SIGNAL(clicked()), this, SLOT(createLogInDialog()));
  this->_core.addErrorListener(this);
  this->_core.addDisconnectListener(this);
}

void		LoginDialog::display()
{
  this->close();
}

void		LoginDialog::onLogin(const QString& username)
{
  std::cout << __FUNCTION__ << std::endl;
  this->_mainWindow = new MainWindow(this->_core);
  connect(this->_mainWindow, SIGNAL(closeMainWindow()), this, SLOT(display()));
  this->_mainWindow->setConnectedUserName(username);
  this->_mainWindow->show();
  this->hide();
}

void		LoginDialog::onRegister(const QString& username)
{
  std::cout << __FUNCTION__ << std::endl;
  this->_mainWindow = new MainWindow(this->_core);
  connect(this->_mainWindow, SIGNAL(closeMainWindow()), this, SLOT(display()));
  this->_mainWindow->setConnectedUserName(username);
  this->_mainWindow->show();
  this->hide();
}

void		LoginDialog::createLogInDialog()
{
  std::cout << __FUNCTION__ << std::endl;
  if (this->_loginDialog)
    {
      this->_core.deleteLoginListener(this->_loginDialog);
      delete this->_loginDialog;
    }
  this->_loginDialog = new LoginEntryDialog(this->_core, this);
  this->_core.addLoginListener(this->_loginDialog);
  this->_loginDialog->show();
}

void		LoginDialog::createSignInDialog()
{
  std::cout << __FUNCTION__ << std::endl;
  if (this->_registerDialog)
    {
      this->_core.deleteRegisterListener(this->_registerDialog);
      delete this->_registerDialog;
    }
  this->_registerDialog = new RegisterEntryDialog(this->_core, this);
  this->_core.addRegisterListener(this->_registerDialog);
  this->_registerDialog->show();
}

void		LoginDialog::onError(QString error)
{
  std::cerr << "\033[31m" << error.toStdString() << "\033[0m" << std::endl;
  this->close();
}

void		LoginDialog::onDisconnect()
{
  this->close();
}

LoginDialog::~LoginDialog() {}
