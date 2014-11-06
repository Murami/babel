#ifndef		__ILOGINLISTENER_HH__
# define	__ILOGINLISTENER_HH__

# include	"Protocol.hh"

class		ILoginListener
{
public:
  virtual void	onLogin(bool) = 0;
};

#endif
