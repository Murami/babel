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
						 const std::string& user,
						 QWidget *parent) :
  QWidget(parent), _core(core)
{
  QVBoxLayout		*layout;
  QLabel		*img;

  core.addCallErrorListener(this);
  this->setFixedSize(AudioConversationWindow::WIDTH, AudioConversationWindow::HEIGHT);
  this->setWindowTitle(QString("Audio call - ") + QString(user.c_str()));

  layout = new QVBoxLayout();
  this->_hangoutButton = new WidgetButton("Hangout", this);
  this->_hangoutButton->setFixedSize(200, 50);
  // ######### FAIRE UNE FONCTION QUI CHANGE LE STATE DU BOUTON

  img = new QLabel();
  img->setPixmap((*ResourceManager::getInstance()->getCallBackground()).scaled(img->size().width(), img->size().height() - 100));
  layout->addWidget(img);
  layout->addWidget(this->_hangoutButton);
  this->setLayout(layout);
  connect(this->_hangoutButton, SIGNAL(clicked()), this, SLOT(hangout()));
  this->_core.onUserCall(QString(user.c_str()));
}

void		AudioConversationWindow::onCallError(bool lol)
{
  if (lol)
    {
      std::cerr << "[ AUDIO ] : Got an error on true" << std::endl;
    }
  else
    {
      std::cerr << "[ AUDIO ] : Got an error on false" << std::endl;
    }
}

void		AudioConversationWindow::hangout()
{
  this->_core.onUserHangout(this->_username);
  emit closed();
  this->close();
}

void		AudioConversationWindow::setUsername(const QString& username)
{
  this->_username = username;
}

AudioConversationWindow::~AudioConversationWindow() {}
