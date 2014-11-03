#include	<QMovie>
#include	<iostream>
#include	"ConversationWindow.hh"
#include	"WidgetButton.hh"
#include	"WidgetTextView.hh"

int		ConversationWindow::WIDTH = 1280;
int		ConversationWindow::HEIGHT = 960;

ConversationWindow::ConversationWindow(QWidget *parent) : QWidget(parent)
{
  QPalette		palette;
  QHBoxLayout		*layout;
  QHBoxLayout		*secondLayout;
  QMovie		*movie;

  palette.setBrush(QPalette::Active,
  		   QPalette::Window, QBrush(QImage("./res/background_conversation.jpg")));
  palette.setBrush(QPalette::Inactive,
  		   QPalette::Window, QBrush(QImage("./res/background_conversation.jpg")));
  this->setPalette(palette);
  this->setFixedSize(ConversationWindow::WIDTH, ConversationWindow::HEIGHT);
  this->setWindowTitle("Conversation");
  //this->_hangoutButton = new WidgetButton("Hangout", this);

  this->_video = new QLabel(this);

  movie = new QMovie("example_video.jpg");
  this->_video->setMovie(movie);
  movie->start();

  this->_sendMessageButton = new WidgetButton("Send", this);
  this->_quitButton = new WidgetButton("Close", this);
  this->_mainLayout = new QVBoxLayout();
  layout = new QHBoxLayout();
  secondLayout = new QHBoxLayout();
  this->_messageTextView = new WidgetTextView(this);
  this->_messageTextView->setEnabled(false);
  this->_messageEdit = new QLineEdit(this);
  this->_messageEdit->setFocus();
  secondLayout->addWidget(this->_messageTextView);
  secondLayout->addWidget(this->_video);
  this->_mainLayout->addLayout(secondLayout);
  //this->_mainLayout->addWidget(this->_messageTextView);
  this->_mainLayout->addWidget(this->_messageEdit);
  layout->addWidget(this->_sendMessageButton);
  layout->addWidget(this->_quitButton);
  this->_mainLayout->addLayout(layout);
  //mainLayout->addWidget(hangoutButton);
  this->setLayout(this->_mainLayout);
  connect(this->_quitButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(this->_messageEdit, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
  connect(this->_sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

void		ConversationWindow::sendMessage()
{
  QString	str;

  std::cout << this->_messageEdit->text().toStdString() << std::endl;
  str = QString(this->_messageTextView->toPlainText());
  str += this->_messageEdit->text();
  str += QString("\n");
  this->_messageTextView->setText(str);
  this->_messageEdit->clear();
}

ConversationWindow::~ConversationWindow() {}
