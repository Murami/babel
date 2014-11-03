#ifndef		__IDISCONNECTLISTENER_HH__
# define	__IDISCONNECTLISTENER_HH__

# include	"Protocol.hh"

class		IDisconnectListener
{
public:
  virtual void	onData(void) = 0;
};

#endif
