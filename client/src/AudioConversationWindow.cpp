#include	<QPixmap>
#include	<QVBoxLayout>
#include	<QMainWindow>
#include	<QLabel>

#include	"ResourceManager.hpp"
#include	"WidgetButton.hh"
#include	"AudioConversationWindow.hh"
#include	"BabelCoreClient.hh"

int		AudioConversationWindow::WIDTH = 640;
int		AudioConversationWindow::HEIGHT = 480;

AudioConversationWindow::AudioConversationWindow(BabelCoreClient& core,
						 const std::string& mate,
						 const std::string&,
						 QWidget *parent) :
  QWidget(parent), _core(core)
{
  QVBoxLayout		*layout;

  core.addKoCallListener(this);
  core.addCallErrorListener(this);
  this->setFixedSize(AudioConversationWindow::WIDTH, AudioConversationWindow::HEIGHT);
  this->setWindowTitle(QString("Audio call - ") + QString(mate.c_str()));
  this->_username = QString(mate.c_str());
  layout = new QVBoxLayout();
  this->_hangoutButton = new WidgetButton("Hangout", this);
  this->_hangoutButton->setFixedSize(200, 50);
  this->_background = new QLabel();
  this->_background->setPixmap((*ResourceManager::getInstance()->getWaitCallBackground()).scaled(this->_background->size().width(), this->_background->size().height() - 100));
  layout->addWidget(this->_background);
  layout->addWidget(this->_hangoutButton);
  this->setLayout(layout);
  connect(this->_hangoutButton, SIGNAL(clicked()), this, SLOT(hangout()));
}

void		AudioConversationWindow::onKoCall()
{
  emit closed();
}

void		AudioConversationWindow::onCallError(bool lol)
{
  if (!lol)
    emit closed();
  else
    this->_background->setPixmap((*ResourceManager::getInstance()->getCallBackground()).scaled(this->_background->size().width(), this->_background->size().height() - 100));
}

void		AudioConversationWindow::hangout()
{
  this->_core.onUserHangout(this->_username);
  emit closed();
}

void		AudioConversationWindow::setUsername(const QString& username)
{
  this->_username = username;
}

AudioConversationWindow::~AudioConversationWindow()
{
  this->_core.deleteCallErrorListener(this);
  this->_core.deleteKoCallListener(this);
}
