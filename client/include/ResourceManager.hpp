#ifndef		__RESOURCEMANAGER_HPP__
# define	__RESOURCEMANAGER_HPP__

# include	<QIcon>
# include	<QPixmap>
# include	<string>
# include	"Protocol.hh"

class		ResourcePath
{
public:
  static std::string	BUTTON_NORMAL;
  static std::string	BUTTON_HOVERED;
  static std::string	BUTTON_PRESSED;
  static std::string	BLUE_PELLET;
  static std::string	RED_PELLET;
};

class		ResourceManager
{
private:
  QPixmap	*_button[3];
  QIcon		*_pellets[2];

private:
  static ResourceManager	*_instance;

public:		ResourceManager()
  {
    _button[0] = new QPixmap(QString(ResourcePath::BUTTON_NORMAL.c_str()));
    _button[1] = new QPixmap(QString(ResourcePath::BUTTON_HOVERED.c_str()));
    _button[2] = new QPixmap(QString(ResourcePath::BUTTON_PRESSED.c_str()));
    _pellets[0] = new QIcon(QString(ResourcePath::BLUE_PELLET.c_str()));
    _pellets[1] = new QIcon(QString(ResourcePath::RED_PELLET.c_str()));
  }

  QIcon			getPellet(NET::Status s)
  {
    return (s == NET::CONNECTED ? *_pellets[0] : *_pellets[1]);
  }

  QPixmap*		getNormalButtonPixmap()
  {
    return (_button[0]);
  }

  QPixmap*		getHoveredButtonPixmap()
  {
    return (_button[1]);
  }

  QPixmap*		getPressedButtonPixmap()
  {
    return (_button[2]);
  }

  static ResourceManager*	getInstance()
  {
    if (_instance == NULL)
      _instance = new ResourceManager();
    return (_instance);
  }

public:		~ResourceManager()
  {
    // Free de toutes les resources
  }
};

#endif
