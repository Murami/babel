#ifndef		__IMSGLISTENER_HH__
# define	__IMSGLISTENER_HH__

# include	"Protocol.hh"

class		IMsgListener
{
public:
  virtual void	onMsg(NET::MsgInfo) = 0;
};

#endif
