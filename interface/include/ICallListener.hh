#ifndef		__ICALLLISTENER_HH__
# define	__ICALLLISTENER_HH__

# include	"Protocol.hh"

class		ICallListener
{
public:
  virtual void	onData(NET::CallInfo) = 0;
};

#endif
