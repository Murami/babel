//
// BabelAccountEntry.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 17:56:15 2014 anto
// Last update Tue Oct 21 18:01:45 2014 anto
//

#ifndef BABELACCOUNTENTRY_HH
#define BABELACCOUNTENTRY_HH

#include "BabelConstant.hh"

struct BabelSessionData;

struct BabelAccountEntry
{
  char			login[LOGIN_SIZE];
  char			md5pass[MD5PASS_SIZE];
  BabelSessionData*	sessionData;
};

#endif /* BABELACCOUNTENTRY_HH */
