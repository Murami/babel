#include	<QMainWindow>
#include	"AudioConversationWindow.hh"
#include	"BabelCoreClient.hh"

int		AudioConversationWindow::WIDTH = 640;
int		AudioConversationWindow::HEIGHT = 480;

AudioConversationWindow::AudioConversationWindow(BabelCoreClient& core, const std::string& username, QWidget *parent) :
  QMainWindow(parent), _core(core)
{
  this->setFixedSize(AudioConversationWindow::WIDTH, AudioConversationWindow::HEIGHT);
  this->setWindowTitle(QString("Audio call - ") + QString(username.c_str()));
}

void		AudioConversationWindow::setUsername(const QString& username)
{
  this->_username = username;
}

AudioConversationWindow::~AudioConversationWindow() {}
