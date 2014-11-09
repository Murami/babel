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

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  BabelCoreClient core;
  //MainWindow mainWindow(core, &w);
  LoginDialog w(core);

  w.show();
  return app.exec();
}
