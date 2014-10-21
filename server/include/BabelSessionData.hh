//
// BabelSessionData.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 18:00:53 2014 anto
// Last update Tue Oct 21 18:03:26 2014 anto
//

#ifndef BABELSESSIONDATA_HH
#define BABELSESSIONDATA_HH

struct BabelAccountEntry;
class BabelCall;

struct BabelSessionData
{
  BabelCall*		call;
  bool			connected;
  BabelAccountEntry*	accountEntry;
};

#endif /* BABELSESSIONDATA_HH */
