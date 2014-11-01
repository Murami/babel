#ifndef _BABEL_ACCOUNT_ENTRY_
# define _BABEL_ACCOUNT_ENTRY_

const unsigned int	LOGIN_SIZE = 256;
const unsigned int	MD5PASS_SIZE = 256;

class BabelSessionData;

struct BabelAccountEntry
{
  char			login[LOGIN_SIZE];
  char			md5pass[MD5PASS_SIZE];
  BabelSessionData*	session;
};

#endif /* _BABEL_ACCOUNT_ENTRY_ */
