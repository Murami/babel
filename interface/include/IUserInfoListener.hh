#ifndef		__IUSERINFOLISTENER_HH__
# define	__IUSERINFOLISTENER_HH__

# include	"Protocol.hh"

class		IUserInfoListener
{
public:
  virtual void	onData(NET::UserInfo) = 0;
};

#endif
