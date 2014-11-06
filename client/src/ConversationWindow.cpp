#include	<QDesktopWidget>
#include	<QMovie>
#include	<iostream>
#include	"ConversationWindow.hh"
#include	"WidgetButton.hh"
#include	"WidgetTextView.hh"
#include	"BabelCoreClient.hh"

int		ConversationWindow::WIDTH = 640;
int		ConversationWindow::HEIGHT = 480;

ConversationWindow::ConversationWindow(BabelCoreClient& core, const std::string& username, QWidget *parent) : QWidget(parent), _core(core)
{
  QVBoxLayout		*mainLayout;
  QHBoxLayout		*layout;
  QDesktopWidget screen;

  this->move(screen.screenGeometry(0).width() / 2 - ConversationWindow::WIDTH / 2,
	     screen.screenGeometry(0).height() / 2 - ConversationWindow::HEIGHT / 2);

  this->setFixedSize(ConversationWindow::WIDTH, ConversationWindow::HEIGHT);
  this->setWindowTitle(QString("Chat - ") + QString(username.c_str()));

  this->_connectedMate = QString(username.c_str());

  this->_sendMessageButton = new WidgetButton("Send");
  this->_quitButton = new WidgetButton("Close");
  layout = new QHBoxLayout();
  mainLayout = new QVBoxLayout();
  this->_messageTextView = new WidgetTextView();
  this->_messageEdit = new QLineEdit();

  this->_messageEdit->setFocus();
  this->_messageTextView->setEnabled(false);
  mainLayout->addWidget(this->_messageTextView);
  mainLayout->addWidget(this->_messageEdit);
  layout->addWidget(this->_sendMessageButton);
  layout->addWidget(this->_quitButton);
  mainLayout->addLayout(layout);
  this->setLayout(mainLayout);

  connect(this->_quitButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(this->_messageEdit, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
  connect(this->_sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
  this->_core.addMsgListener(this);
}

void		ConversationWindow::setUsername(const QString& username)
{
  this->_username = username;
}

void		ConversationWindow::_format()
{
  QTextCursor cur( this->_messageTextView->document() );

  // indent first paragraph
  QTextBlockFormat f( cur.blockFormat() ); // note: you get a copy of the format

  f.setIndent( 1 );
  cur.setBlockFormat( f ); // here you replace the format used in document

  // move to next paragraph
  if( cur.movePosition( QTextCursor::NextBlock ) )
    {

      // select first line
      cur.movePosition( QTextCursor::StartOfLine );
      cur.movePosition( QTextCursor::EndOfLine, QTextCursor::KeepAnchor );
      // note that what "line" means depends on the size of text edit --- resize the 
      // window to see how it behaves

      // underline selected line
      QTextCharFormat f( cur.charFormat() );
      f.setFontUnderline( true );
      cur.setCharFormat( f );
    }
}

void		ConversationWindow::onMsg(NET::MsgInfo info)
{
  QString	str;

  str = QString(info.msg);
  //this->_format();
  this->_messageTextView->append(str);
}

void		ConversationWindow::sendMessage()
{
  QString str;

   str = this->_messageEdit->text();
   this->_messageEdit->clear();
   this->_messageTextView->append(str);
   this->_core.onUserMsg(this->_connectedMate, str);
 }

ConversationWindow::~ConversationWindow() {}
