#ifndef		__ILOGINLISTENER_HH__
# define	__ILOGINLISTENER_HH__

# include	"Protocol.hh"

class		ILoginListener
{
public:
  virtual void	onData(bool) = 0;
};

#endif
