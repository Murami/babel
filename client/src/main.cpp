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

std::string	ResourcePath::WAIT_BACKGROUND	= "./res/wait_background.jpg";
std::string	ResourcePath::CALL_BACKGROUND	= "./res/call_background.jpg";
std::string	ResourcePath::BUTTON_NORMAL	= "./res/button_normal.jpg";
std::string	ResourcePath::BUTTON_HOVERED	= "./res/button_hovered.jpg";
std::string	ResourcePath::BUTTON_PRESSED	= "./res/button_pressed.jpg";
std::string	ResourcePath::BLUE_PELLET	= "./res/blue_pellet.png";
std::string	ResourcePath::RED_PELLET	= "./res/red_pellet.png";
ResourceManager	*ResourceManager::_instance	= NULL;



// #include "main.hh"

// #define PORT 4253

// ClientReader::ClientReader(QWidget *parent) : QWidget(parent)
// {
// }

// void ClientReader::bind()
// {
//   QObject::connect(&this->sock, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(setReadyRead(QAbstractSocket::SocketState)));
//   this->sock.bind(QHostAddress::Any, PORT);
// }

// void ClientReader::setReadyRead(QAbstractSocket::SocketState s)
// {
//   std::cout << "change state " << s << std::endl;
//   if (s == QAbstractSocket::BoundState)
//     {
//       std::cout << "connect readyRead" << std::endl;
//       QObject::connect(&this->sock, SIGNAL(readyRead()), this, SLOT(readUdp()));
//     }
// }

// void ClientReader::writeUdp(test *t)
// {
//   std::cout << "Writing " << t->n << std::endl;
//   sock.writeDatagram((char*)t, sizeof(*t), QHostAddress::Any, PORT);
// }

// void ClientReader::readUdp()
// {
//   test t;

//   std::cout << "read : ";
//   sock.readDatagram((char*)&t, (qint64)sizeof(t));
//   std::cout << " [" << t.n << "]" << std::endl;
// }

// #include <unistd.h>

// ClientReader::~ClientReader()
// {
//   std::cout << "coucuo" << std::endl;
//   this->sock.close();
// }

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // ClientReader reader;

  // if (argc == 1)
  //   {
  //     test t;
  //     t.n = 42;
  //     while (true)
  // 	{
  // 	  reader.writeUdp(&t);
  // 	  sleep(1);
  // 	}
  //   }
  // else
  //   reader.bind();

  BabelCoreClient core;
  LoginDialog w(core);

  w.show();
  return app.exec();
}
