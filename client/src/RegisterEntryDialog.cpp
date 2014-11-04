#include	<iostream>
#include	"RegisterEntryDialog.hh"
#include	"BabelCoreClient.hh"

RegisterEntryDialog::RegisterEntryDialog(BabelCoreClient& core, QWidget *parent)
  : QDialog(parent), _core(core)
{
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
  connect(this->_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  core.addRegisterListener(this);
}

void		RegisterEntryDialog::onData(bool ok)
{
  std::cout << "REGISTER STATE : " << std::boolalpha << ok << std::endl;
}

RegisterEntryDialog::~RegisterEntryDialog() {}
