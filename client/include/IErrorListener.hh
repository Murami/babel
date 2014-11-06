#ifndef		__IERRORLISTENER_HH__
# define	__IERRORLISTENER_HH__

# include	<QString>
# include	"Protocol.hh"

class		IErrorListener
{
public:
  virtual void	onError(QString) = 0;
};

#endif
