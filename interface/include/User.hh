#ifndef		__USER_HH__
# define	__USER_HH__

# include	<string>

class		User
{
private:
  std::string	_name;
  bool		_connected;

public:
  void		setName(const std::string&);
  void		setConnected(bool);

public:
  const std::string&	getName() const;
  bool			isConnected() const;

public:
  User(const std::string&, bool connected = false);
  ~User();
};

#endif
