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

std::string	ResourcePath::WAIT_BACKGROUND	= ":/background/wait";
std::string	ResourcePath::CALL_BACKGROUND	= ":/background/call";
std::string	ResourcePath::BUTTON_NORMAL	= ":/button/normal";
std::string	ResourcePath::BUTTON_HOVERED	= ":/button/hovered";
std::string	ResourcePath::BUTTON_PRESSED	= ":/button/pressed";
std::string	ResourcePath::BLUE_PELLET	= ":/pellet/blue";
std::string	ResourcePath::RED_PELLET	= ":/pellet/red";
ResourceManager	*ResourceManager::_instance	= NULL;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  BabelCoreClient core;
  LoginDialog w(core);

  w.show();
  return app.exec();
}
