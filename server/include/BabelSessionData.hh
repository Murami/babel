#ifndef _BABEL_SESSION_DATA_
# define _BABEL_SESSION_DATA_

class BabelCall;
class BabelAccountEntry;

struct BabelSessionData
{
  BabelCall*		call;
  bool			connected;
  BabelAccountEntry*	entry;
};

#endif /* _BABEL_SESSION_DATA_ */
