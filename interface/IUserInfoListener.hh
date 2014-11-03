#ifndef		__IUSERINFOLISTENER_HH__
# define	__IUSERINFOLISTENER_HH__

class		IUserInfoListener
{
public:
  virtual void	onData(UserInfo) = 0;
};

#endif
