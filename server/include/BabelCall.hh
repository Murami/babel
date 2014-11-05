#ifndef	_BABEL_CALL_
# define _BABEL_CALL_

class BabelClient;

class BabelCall
{

public:
  BabelCall(BabelClient*, BabelClient*);
  ~BabelCall();

  BabelClient*		getDestination();
  BabelClient*		getInterluctor(BabelClient*);
  BabelClient*		getSource();
  unsigned int		getTimestart() const;
  bool			isValid() const;
  void			setValid(bool b);


private:
  BabelClient*		m_destination;
  BabelClient*		m_source;
  unsigned int		m_timer;
  bool			m_isValid;
};

#endif /* _BABEL_CALL_ */
