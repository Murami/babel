#include	"User.hh"

User::User(const std::string& name, bool connected)
{
  this->_name = name;
  this->_connected = connected;
}

void		User::setName(const std::string& name)
{
  this->_name = name;
}

void		User::setConnected(bool connected)
{
  this->_connected = connected;
}

const std::string&	User::getName() const
{
  return (this->_name);
}

bool		User::isConnected() const
{
  return (this->_connected);
}

User::~User() {}
