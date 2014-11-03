#ifndef		__IMSGLISTENER_HH__
# define	__IMSGLISTENER_HH__

class		IMsgListener
{
public:
  virtual void	onData(MsgInfo) = 0;
};

#endif
