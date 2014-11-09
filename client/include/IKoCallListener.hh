#ifndef		__IKOCALLLISTENER_HH__
# define	__IKOCALLLISTENER_HH__

# include	"Protocol.hh"

class		IKoCallListener
{
public:
  virtual void	onKoCall() = 0;
};

#endif
