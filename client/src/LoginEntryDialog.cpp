#include	<iostream>
#include	"LoginEntryDialog.hh"
#include	"WidgetButton.hh"
#include	"BabelCoreClient.hh"

LoginEntryDialog::LoginEntryDialog(BabelCoreClient& core, QWidget *parent) : QDialog(parent), _core(core)
{
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
  core.addLoginListener(this);
}

void		LoginEntryDialog::sendData()
{
  this->_core.onUserLogin(this->_pseudoEdit->text(), this->_passwordEdit->text());
}

void		LoginEntryDialog::onData(bool ok)
{
  std::cout << "LOGIN STATE : " << std::boolalpha << ok << std::endl;
}

LoginEntryDialog::~LoginEntryDialog() {}
