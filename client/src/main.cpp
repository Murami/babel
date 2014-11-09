#include <QString>
#include <QApplication>
#include <QPushButton>
#include <QtNetwork>

#include <QSettings>

#include "BabelCoreClient.hh"
#include "ResourceManager.hpp"
#include "MainWindow.hh"
#include "LoginDialog.hh"
#include "LoginEntryDialog.hh"
#include "RegisterEntryDialog.hh"

#include "main.hh"

std::string	ResourcePath::CALL_BACKGROUND	= "./res/call_background.jpg";
std::string	ResourcePath::BUTTON_NORMAL	= "./res/button_normal.jpg";
std::string	ResourcePath::BUTTON_HOVERED	= "./res/button_hovered.jpg";
std::string	ResourcePath::BUTTON_PRESSED	= "./res/button_pressed.jpg";
std::string	ResourcePath::BLUE_PELLET	= "./res/blue_pellet.png";
std::string	ResourcePath::RED_PELLET	= "./res/red_pellet.png";
ResourceManager	*ResourceManager::_instance	= NULL;



ClientReader::ClientReader(QWidget *parent) : QWidget(parent)
{
  QObject::connect(&this->sock, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(setReadyRead(QAbstractSocket::SocketState)));
  std::cout << "bind : " << this->sock.bind(QHostAddress::Any, 4242, QUdpSocket::ShareAddress) << std::endl;
  std::cout << sock.bytesAvailable() << std::endl;
}

void ClientReader::setReadyRead(QAbstractSocket::SocketState s)
{
  std::cout << "change state " << s << std::endl;
  if (s == QAbstractSocket::BoundState)
    {
      std::cout << "connect readyRead" << std::endl;
      QObject::connect(&this->sock, SIGNAL(readyRead()), this, SLOT(readUdp()));
      this->sock.seek(0);
    }
}

void ClientReader::readUdp()
{
  test t;

  std::cout << "read" << std::endl;
  std::cout << "ret " << sock.readDatagram((char*)&t, sizeof(t), NULL, NULL) << std::endl;
  std::cout << t.n << std::endl;
}

#include <unistd.h>

ClientReader::~ClientReader() {}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // BabelCoreClient core;
  // //MainWindow mainWindow(core, &w);
  // LoginDialog w(core);

  // w.show();
  // return app.exec();

  ClientReader reader;
  test t;
  t.n = 42;

  char b[4096];

  memset(b, 0x0D, 4096);
  memcpy(b, &t, sizeof(t));

  std::string toto;

  if (argc == 1)
    while(1)
      {
	std::cout << reader.sock.writeDatagram((char*)&t, sizeof(t), QHostAddress("0.0.0.0"), 4242) << std::endl;
	reader.sock.flush();
	sleep(1);
      }
  app.exec();
}
