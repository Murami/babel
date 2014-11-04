#include	<iostream>
#include	"AddNewContactDialog.hh"
#include	"IWidgetListener.hh"

AddNewContactDialog::AddNewContactDialog(QWidget *parent) : QDialog(parent)
{
  this->_tagEdit = new QLineEdit(this);
  this->_tagEdit->setBackgroundRole(QPalette::Background);
  this->setWindowTitle("Add new contact");
  this->_addButton = new WidgetButton("Add", this);
  this->_addButton->setFixedSize(100, 50);
  this->_cancelButton = new WidgetButton("Cancel", this);
  this->_cancelButton->setFixedSize(100, 50);
  this->_vlayout = new QVBoxLayout();
  this->_hlayout = new QHBoxLayout();
  this->_tagEdit->setPlaceholderText("BabelTag");
  this->_vlayout->addWidget(this->_tagEdit);
  this->_hlayout->addWidget(this->_addButton);
  this->_hlayout->addWidget(this->_cancelButton);
  this->_vlayout->addLayout(this->_hlayout);
  this->_addButton->setFocus();
  this->setLayout(this->_vlayout);
  connect(this->_addButton, SIGNAL(clicked()), this, SLOT(sendRequest()));
  connect(this->_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void		AddNewContactDialog::sendRequest()
{
  std::cout << this->_tagEdit->text().toStdString() << std::endl;
  // Appeler onUserRegiser du IWidgetListener
}

AddNewContactDialog::~AddNewContactDialog() {}
