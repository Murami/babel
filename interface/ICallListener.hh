#ifndef		__ICALLLISTENER_HH__
# define	__ICALLLISTENER_HH__

class		ICallListener
{
public:
  virtual void	onData(CallInfo) = 0;
};

#endif
