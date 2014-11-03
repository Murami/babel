#include	<iostream>
#include	"AddNewContactDialog.hh"

AddNewContactDialog::AddNewContactDialog(QWidget *parent) : QDialog(parent)
{
  this->_palette.setBrush(QPalette::Active,
			  QPalette::Window, QBrush(QImage("./res/background_main.jpg")));
  this->_palette.setBrush(QPalette::Inactive,
			  QPalette::Window, QBrush(QImage("./res/background_main.jpg")));
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
  this->setLayout(this->_vlayout);
  connect(this->_addButton, SIGNAL(clicked()), this, SLOT(sendRequest()));
}

void		AddNewContactDialog::sendRequest()
{
  std::cout << this->_tagEdit->text().toStdString() << std::endl;
}

AddNewContactDialog::~AddNewContactDialog() {}
