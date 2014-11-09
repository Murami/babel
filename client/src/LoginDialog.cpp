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
  if (parent != 0)
    this->_mainWindow = static_cast<MainWindow*>(parent);
  else
    this->_mainWindow = new MainWindow(core);

  this->_loginDialog = new LoginEntryDialog(this->_core, this);
  this->_core.addLoginListener(this->_loginDialog);
  this->_registerDialog = new RegisterEntryDialog(this->_core, this);
  this->_core.addRegisterListener(this->_registerDialog);

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
  connect(this->_mainWindow, SIGNAL(closeMainWindow()), this, SLOT(display()));
  core.addErrorListener(this);
  core.addDisconnectListener(this);
}

void		LoginDialog::display()
{
  this->_mainWindow->deleteAudioWindow();
  this->show();
}

void		LoginDialog::onLogin(const QString& username)
{
  this->_mainWindow->setConnectedUserName(username);
  this->_mainWindow->show();
  this->hide();
}

void		LoginDialog::onRegister(const QString& username)
{
  this->_mainWindow->setConnectedUserName(username);
  this->_mainWindow->show();
  this->hide();
}

void		LoginDialog::createLogInDialog()
{
  this->_loginDialog->reset();
  this->_loginDialog->show();
}

void		LoginDialog::createSignInDialog()
{
  this->_registerDialog->reset();
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
