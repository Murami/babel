#include	<QMessageBox>
#include	<iostream>
#include	"LoginEntryDialog.hh"
#include	"WidgetButton.hh"
#include	"BabelCoreClient.hh"
#include	"MainWindow.hh"
#include	"Protocol.hh"
#include	"LoginDialog.hh"

LoginEntryDialog::LoginEntryDialog(BabelCoreClient& core, QWidget *parent) : QDialog(parent), _core(core)
{
  this->_parent = static_cast<LoginDialog*>(parent);
  this->setWindowTitle("Log in");
  this->_vLayout = new QVBoxLayout();
  this->_hLayout = new QHBoxLayout();
  this->_logInButton = new WidgetButton("Log in", this);
  this->_logInButton->setFocus();
  this->_cancelButton = new WidgetButton("Cancel", this);
  this->_pseudoEdit = new QLineEdit(this);
  this->_pseudoEdit->setPlaceholderText("Username");
  this->_passwordEdit = new QLineEdit(this);
  this->_passwordEdit->setPlaceholderText("Password");
  this->_passwordEdit->setEchoMode(QLineEdit::Password);
  this->_vLayout->addWidget(this->_pseudoEdit);
  this->_vLayout->addWidget(this->_passwordEdit);
  this->_hLayout->addWidget(this->_logInButton);
  this->_hLayout->addWidget(this->_cancelButton);
  this->_vLayout->addLayout(this->_hLayout);
  this->setLayout(this->_vLayout);
  connect(this->_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(this->_logInButton, SIGNAL(clicked()), this, SLOT(sendData()));
  connect(this->_passwordEdit, SIGNAL(returnPressed()), this, SLOT(sendData()));
}

void		LoginEntryDialog::onError(QString error)
{
  this->_createErrorBox(QString(""), error);
}

void		LoginEntryDialog::sendData()
{
  QString	pass = this->_passwordEdit->text();

  this->_user = this->_pseudoEdit->text();
  if (this->_user.length() >= LOGIN_SIZE)
    this->_createErrorBox("Login too long",
			  "Login is too long");
  else if (this->_user.length() < 3)
    this->_createErrorBox("Login too short",
			  "Login is too short");
  else
    this->_core.onUserLogin(this->_user, pass);
}

void		LoginEntryDialog::onLogin(bool success)
{
  if (success)
    {
      this->_parent->onLogin(this->_user);
      this->close();
    }
  else
    this->_createErrorBox("Unable to log in",
			  "Error : combination login/password is not correct");
}

void		LoginEntryDialog::_createErrorBox(const QString& title, const QString& msg)
{
  QMessageBox *box = new QMessageBox(this);
  box->setWindowTitle(title);
  box->setText(msg);
  box->setIcon(QMessageBox::Critical);
  box->show();
}

LoginEntryDialog::~LoginEntryDialog() {}
