#ifndef		__IDISCONNECTLISTENER_HH__
# define	__IDISCONNECTLISTENER_HH__

# include	"Protocol.hh"

class		IDisconnectListener
{
public:
  virtual void	onDisconnect(void) = 0;
};

#endif
