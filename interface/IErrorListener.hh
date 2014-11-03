#ifndef		__IERRORLISTENER_HH__
# define	__IERRORLISTENER_HH__

# include	<QAbstractSocket>

class		IErrorListener
{
public:
  virtual void	onData(QAbstractSocket::SocketError) = 0;
};

#endif
