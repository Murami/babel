#include	<QApplication>

#include	"ResourceManager.hpp"
#include	"MainWindow.hh"

// TEST
#include	"ConversationWindow.hh"

std::string	ResourcePath::BUTTON_NORMAL = "./res/button_normal.jpg";
std::string	ResourcePath::BUTTON_HOVERED = "./res/button_hovered.jpg";
std::string	ResourcePath::BUTTON_PRESSED = "./res/button_pressed.jpg";
ResourceManager	*ResourceManager::_instance = NULL;

int		main(int argc, char *argv[])
{
  QApplication	app(argc, argv);
  ConversationWindow w2;
  MainWindow	w;

  w.show();
  w2.show();
  return (app.exec());
}
