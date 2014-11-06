#ifndef		__ICALLERRORLISTENER_HH__
# define	__ICALLERRORLISTENER_HH__

class		ICallErrorListener
{
public:
  virtual void	onCallError(bool) = 0;
};

#endif
