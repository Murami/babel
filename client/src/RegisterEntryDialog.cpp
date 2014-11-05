#include	<QMessageBox>
#include	<iostream>
#include	"RegisterEntryDialog.hh"
#include	"BabelCoreClient.hh"
#include	"Protocol.hh"
#include	"LoginDialog.hh"

RegisterEntryDialog::RegisterEntryDialog(BabelCoreClient& core, QWidget *parent)
  : QDialog(parent), _core(core)
{
  this->_parent = static_cast<LoginDialog*>(parent);
  this->setWindowTitle("Sign in");
  this->_vLayout = new QVBoxLayout();
  this->_hLayout = new QHBoxLayout();
  this->_signInButton = new WidgetButton("Sign in", this);
  this->_signInButton->setFocus();
  this->_cancelButton = new WidgetButton("Cancel", this);
  this->_pseudoEdit = new QLineEdit(this);
  this->_pseudoEdit->setPlaceholderText("Choose username");
  this->_passwordEdit1 = new QLineEdit(this);
  this->_passwordEdit1->setPlaceholderText("Choose password");
  this->_passwordEdit1->setEchoMode(QLineEdit::Password);
  this->_passwordEdit2 = new QLineEdit(this);
  this->_passwordEdit2->setPlaceholderText("Retype password");
  this->_passwordEdit2->setEchoMode(QLineEdit::Password);
  this->_vLayout->addWidget(this->_pseudoEdit);
  this->_vLayout->addWidget(this->_passwordEdit1);
  this->_vLayout->addWidget(this->_passwordEdit2);
  this->_hLayout->addWidget(this->_signInButton);
  this->_hLayout->addWidget(this->_cancelButton);
  this->_vLayout->addLayout(this->_hLayout);
  this->setLayout(this->_vLayout);
  connect(this->_pseudoEdit, SIGNAL(returnPressed()), this, SLOT(sendData()));
  connect(this->_passwordEdit1, SIGNAL(returnPressed()), this, SLOT(sendData()));
  connect(this->_passwordEdit2, SIGNAL(returnPressed()), this, SLOT(sendData()));

  // ##### REMETTRE LE CANCEL QUAND J'AURAI COMPRIS POURQUOI EST-CE QU'IL NE MARCHE PAS !
  // ##### PARCE QUE LE CANCEL EST APPELE LORS DE L'APPUI SUR ENTER
  //connect(this->_cancelButton, SIGNAL(clicked()), this, SLOT(close()));

  connect(this->_signInButton, SIGNAL(clicked()), this, SLOT(sendData()));
  // core.addRegisterListener(this);
}

void		RegisterEntryDialog::sendData()
{
  QString	user = this->_pseudoEdit->text();
  QString	pass = this->_passwordEdit1->text();
  QString	passCheck = this->_passwordEdit2->text();

  if (user.length() >= LOGIN_SIZE)
    this->_createErrorBox("Login too long",
			  "Login is too long");
  else if (user.length() < 3)
    this->_createErrorBox("Login too short",
			  "Login is too short");
  else if (pass.length() == 0)
    this->_createErrorBox("Empty password", "Password cannot be empty");
  else if (passCheck.length() == 0)
    this->_createErrorBox("Password not confirmed", "Please confirm your password");
  else if (pass != passCheck)
    this->_createErrorBox("Password mismatch",
			  "Passwords must be identical");
  else
    this->_core.onUserRegister(user, pass);
}

void		RegisterEntryDialog::onData(bool success)
{
  if (success)
    {
      this->_parent->onRegister(this->_pseudoEdit->text());
      this->close();
    }
  else
    this->_createErrorBox("Unable to register",
			  "Error : unable to register to Babel");
}

void		RegisterEntryDialog::_createErrorBox(const QString& title, const QString& msg)
{
  QMessageBox *box = new QMessageBox(this);
  box->setWindowTitle(title);
  box->setText(msg);
  box->setIcon(QMessageBox::Critical);
  box->show();
}

RegisterEntryDialog::~RegisterEntryDialog() {}
