//
// BabelCall.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 21:59:39 2014 anto
// Last update Tue Oct 21 22:12:30 2014 anto
//

#ifndef BABELCALL_HH
#define BABELCALL_HH

struct TcpAsyncSession;

class BabelCall
{
private:
  TcpAsyncSession*	m_source;
  TcpAsyncSession*	m_destination;
  unsigned int		m_timestart;

public:
  BabelCall(TcpAsyncSession* babelSessionSource, TcpAsyncSession* babelSessionDestination);
  ~BabelCall();

  TcpAsyncSession*	getSource() const;
  TcpAsyncSession*	getDestination() const;
  TcpAsyncSession*	getInterlocutor() const;
  unsigned int		getTimestart() const;
};

#endif /* BABELCALL_HH */
