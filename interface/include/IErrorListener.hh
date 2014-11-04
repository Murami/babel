#ifndef		__IERRORLISTENER_HH__
# define	__IERRORLISTENER_HH__

# include	"Protocol.hh"

class		IErrorListener
{
public:
  virtual void	onData(QString) = 0;
};

#endif
