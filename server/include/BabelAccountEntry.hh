#ifndef BABELACCOUNTENTRY_HH
#define BABELACCOUNTENTRY_HH

struct BabelAccountEntry
{
  char			login[LOGIN_SIZE];
  char			md5pass[MD5PASS_SIZE];
  BabelSessionData*	sessionData;
};

#endif /* BABELACCOUNTENTRY_HH */
