#ifndef		__IERRORLISTENER_HH__
# define	__IERRORLISTENER_HH__

# include	"Protocol.hh"

class		IErrorListener
{
public:
  virtual void	onData(char *) = 0;
};

#endif
