#ifndef		__ICONNECTLISTENER_HH__
# define	__ICONNECTLISTENER_HH__

# include	"Protocol.hh"

class		IConnectListener
{
public:
  virtual void	onConnect(void) = 0;
};

#endif
