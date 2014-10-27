//
// Babel.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Mon Oct 27 16:04:45 2014 anto
// Last update Mon Oct 27 16:23:03 2014 anto
//

#ifndef BABEL_HH
#define BABEL_HH

class AsyncService;

class Babel
{
private:
  AsyncService*	m_service;

public:
  Babel();
  ~Babel();

  int	run();
};

#endif /* BABEL_HH */
