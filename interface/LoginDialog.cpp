#include	<QLineEdit>
#include	<iostream>
#include	"WidgetButton.hh"
#include	"LoginDialog.hh"

int		LoginDialog::WIDTH = 640;
int		LoginDialog::HEIGHT = 480;

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
  QPalette	palette;

  palette.setBrush(QPalette::Active, QPalette::Window, QBrush(QImage("./background_login.jpg")));
  palette.setBrush(QPalette::Inactive, QPalette::Window, QBrush(QImage("./background_login.jpg")));
  this->setPalette(palette);
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
}

void		LoginDialog::createLogInDialog()
{
  QVBoxLayout	*vLayout;
  QHBoxLayout	*hLayout;
  QPushButton	*logInButton;
  QPushButton	*cancelButton;
  QLineEdit	*pseudoEdit;
  QLineEdit	*passwordEdit;
  QDialog	*dialog;
  QPalette	palette;

  // ##################################################################
  // ### Connecter les boutons sur l'envoi des datas sur le serveur ###
  // ##################################################################
  palette.setBrush(QPalette::Active, QPalette::Window, QBrush(QImage("./background_login.jpg")));
  palette.setBrush(QPalette::Inactive, QPalette::Window, QBrush(QImage("./background_login.jpg")));
  dialog = new QDialog(this);
  dialog->setWindowTitle("Log in");
  dialog->setPalette(palette);
  vLayout = new QVBoxLayout();
  hLayout = new QHBoxLayout();
  logInButton = new WidgetButton("Log in", this);
  logInButton->setFocus();
  cancelButton = new WidgetButton("Cancel", this);
  pseudoEdit = new QLineEdit(this);
  pseudoEdit->setPlaceholderText("Username");
  passwordEdit = new QLineEdit(this);
  passwordEdit->setPlaceholderText("Password");
  passwordEdit->setEchoMode(QLineEdit::Password);
  vLayout->addWidget(pseudoEdit);
  vLayout->addWidget(passwordEdit);
  hLayout->addWidget(logInButton);
  hLayout->addWidget(cancelButton);
  vLayout->addLayout(hLayout);
  dialog->setLayout(vLayout);
  dialog->show();
  connect(cancelButton, SIGNAL(clicked()), dialog, SLOT(close()));
}

void		LoginDialog::createSignInDialog()
{
  QVBoxLayout	*vLayout;
  QHBoxLayout	*hLayout;
  QPushButton	*signInButton;
  QPushButton	*cancelButton;
  QLineEdit	*pseudoEdit;
  QLineEdit	*passwordEdit1;
  QLineEdit	*passwordEdit2;
  QDialog	*dialog;
  QPalette	palette;

  // ##################################################################
  // ### Connecter les boutons sur l'envoi des datas sur le serveur ###
  // ##################################################################
  palette.setBrush(QPalette::Active, QPalette::Window, QBrush(QImage("./background_login.jpg")));
  palette.setBrush(QPalette::Inactive, QPalette::Window, QBrush(QImage("./background_login.jpg")));
  dialog = new QDialog(this);
  dialog->setWindowTitle("Sign in");
  dialog->setPalette(palette);
  vLayout = new QVBoxLayout();
  hLayout = new QHBoxLayout();
  signInButton = new WidgetButton("Sign in", this);
  signInButton->setFocus();
  cancelButton = new WidgetButton("Cancel", this);
  pseudoEdit = new QLineEdit(this);
  pseudoEdit->setPlaceholderText("Choose username");
  passwordEdit1 = new QLineEdit(this);
  passwordEdit1->setPlaceholderText("Choose password");
  passwordEdit1->setEchoMode(QLineEdit::Password);
  passwordEdit2 = new QLineEdit(this);
  passwordEdit2->setPlaceholderText("Retype password");
  passwordEdit2->setEchoMode(QLineEdit::Password);
  vLayout->addWidget(pseudoEdit);
  vLayout->addWidget(passwordEdit1);
  vLayout->addWidget(passwordEdit2);
  hLayout->addWidget(signInButton);
  hLayout->addWidget(cancelButton);
  vLayout->addLayout(hLayout);
  dialog->setLayout(vLayout);
  dialog->show();
  connect(cancelButton, SIGNAL(clicked()), dialog, SLOT(close()));
}

LoginDialog::~LoginDialog() {}
