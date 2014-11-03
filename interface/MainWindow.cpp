#include	<QLineEdit>
#include	"ContactListView.hh"
#include	"LoginDialog.hh"
#include	"MainWindow.hh"

#include	"WidgetButton.hh"

int		MainWindow::WIDTH = 800;
int		MainWindow::HEIGHT = 600;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
  QPalette	palette;

  palette.setBrush(QPalette::Active,
		   QPalette::Window, QBrush(QImage("./background_main.jpg")));
  palette.setBrush(QPalette::Inactive,
		   QPalette::Window, QBrush(QImage("./background_main.jpg")));
  this->setPalette(palette);
  this->_contactListView = new ContactListView(this);
  this->_callButton = new WidgetButton("Call", this);
  this->setFixedSize(MainWindow::WIDTH, MainWindow::HEIGHT);
  this->setWindowTitle("Babel");
  this->_mainLayout = new QHBoxLayout(this);
  this->_layout = new QVBoxLayout();
  this->_addContactButton = new WidgetButton("Add contact", this);
  this->_layout->addWidget(this->_callButton);
  this->_layout->setAlignment(this->_callButton, Qt::AlignHCenter);
  this->_layout->addWidget(this->_addContactButton);
  this->_layout->setAlignment(this->_addContactButton, Qt::AlignHCenter);
  this->_mainLayout->addWidget(this->_contactListView);
  this->_mainLayout->addLayout(this->_layout);
  this->_connectButtons();
  this->_loginDialog = new LoginDialog(this);
  this->_loginDialog->show();
}

void		MainWindow::_connectButtons()
{
  connect(this->_callButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(this->_addContactButton, SIGNAL(clicked()), this, SLOT(createNewContactDialog()));
}

void		MainWindow::createNewContactDialog()
{
  QDialog	*dialog;
  QLineEdit	*tagEdit;
  WidgetButton	*addButton;
  WidgetButton	*cancelButton;
  QVBoxLayout	*vlayout;
  QHBoxLayout	*hlayout;
  QPalette	palette;

  palette.setBrush(QPalette::Active,
		   QPalette::Window, QBrush(QImage("./background_main.jpg")));
  palette.setBrush(QPalette::Inactive,
		   QPalette::Window, QBrush(QImage("./background_main.jpg")));
  dialog = new QDialog(this);
  tagEdit = new QLineEdit(dialog);
  dialog->setWindowTitle("Add new contact");
  tagEdit->setPalette(palette);
  addButton = new WidgetButton("Add", dialog);
  addButton->setFixedSize(100, 50);
  cancelButton = new WidgetButton("Cancel", dialog);
  cancelButton->setFixedSize(100, 50);
  vlayout = new QVBoxLayout(dialog);
  hlayout = new QHBoxLayout();
  tagEdit->setPlaceholderText("BabelTag");
  vlayout->addWidget(tagEdit);
  hlayout->addWidget(addButton);
  hlayout->addWidget(cancelButton);
  vlayout->addLayout(hlayout);
  dialog->setLayout(vlayout);
  dialog->show();
}

MainWindow::~MainWindow() {}
