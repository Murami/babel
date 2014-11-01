#ifndef	_BABEL_CALL_
# define _BABEL_CALL_

class BabelCall
{
public:
  BabelCall(TcpAsyncSession*, TcpAsyncSession*);
  ~BabelCall();

  TcpAsyncSession*	getDestination();
  TcpAsyncSession*	getInterluctor();
  TcpAsyncSession*	getSource();
  unsigned int		getTimestart() const;

private:
  TcpAsyncSession*	m_destination;
  TcpAsyncSession*	m_source;
  unsigned int		m_timer;
}

#endif /* _BABEL_CALL_ */
