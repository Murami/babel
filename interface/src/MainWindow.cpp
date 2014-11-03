#include	<iostream>
#include	<QLineEdit>

#include	"WidgetListView.hh"
#include	"LoginDialog.hh"
#include	"MainWindow.hh"

#include	"AddNewContactDialog.hh"
#include	"WidgetButton.hh"

int		MainWindow::WIDTH = 800;
int		MainWindow::HEIGHT = 600;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
  QPalette	palette;

  palette.setBrush(QPalette::Active,
		   QPalette::Window, QBrush(QImage("./res/background_main.jpg")));
  palette.setBrush(QPalette::Inactive,
		   QPalette::Window, QBrush(QImage("./res/background_main.jpg")));
  this->setPalette(palette);
  this->_widgetListView = new WidgetListView(this);
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
  this->_mainLayout->addWidget(this->_widgetListView);
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
  AddNewContactDialog *dialog;

  dialog = new AddNewContactDialog(this);
  dialog->show();
}

MainWindow::~MainWindow() {}
