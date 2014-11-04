#include "Functor.hh"
#include "Protocol.hh"
#include "BabelCoreClient.hh"

void UserInfoFunctor::operator()(BabelCoreClient & core, void *data)
{
  if (core.getTypeNeeded() == NET::T_HEADER)
    core.setTypeNeeded(NET::T_USERINFO);
  else
    {
      core.setTypeNeeded(NET::T_HEADER);
      NET::UserInfo *tmp = reinterpret_cast<NET::UserInfo*>(data);
      core.notifyUserInfo(*tmp);
    }
}

void RecvMsgFunctor::operator()(BabelCoreClient & core, void *data)
{
  if (core.getTypeNeeded() == NET::T_HEADER)
    core.setTypeNeeded(NET::T_RECVMSG);
  else
    {
      core.setTypeNeeded(NET::T_HEADER);
      NET::MsgInfo *tmp = reinterpret_cast<NET::MsgInfo*>(data);
      core.notifyMsg(*tmp);
    }
}

void CallFunctor::operator()(BabelCoreClient & core, void *data)
{
  if (core.getTypeNeeded() == NET::T_HEADER)
    core.setTypeNeeded(NET::T_CALL);
  else
    {
      core.setTypeNeeded(NET::T_HEADER);
      NET::CallInfo *tmp = reinterpret_cast<NET::CallInfo*>(data);
      core.notifyCall(*tmp);
    }
}

void OkLoginFunctor::operator()(BabelCoreClient & core, void *data)
{
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyLogin(true);
}

void KoLoginFunctor::operator()(BabelCoreClient & core, void *data)
{
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyLogin(false);
}

void OkRegisterFunctor::operator()(BabelCoreClient & core, void *data)
{
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyRegister(true);
}

void KoRegisterFunctor::operator()(BabelCoreClient & core, void *data)
{
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyRegister(false);
}

void OkCallFunctor::operator()(BabelCoreClient & core, void *data)
{
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyCallError(true);
}

void KoCallFunctor::operator()(BabelCoreClient & core, void *data)
{
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyCallError(false);
}

void OkMsgFunctor::operator()(BabelCoreClient & core, void *data)
{
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyMsgError(true);
}

void KoMsgFunctor::operator()(BabelCoreClient & core, void *data)
{
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyMsgError(false);
}

void SampleFunctor::operator()(BabelCoreClient & core, void *data)
{

}

void ImgFunctor::operator()(BabelCoreClient & core, void *data)
{

}

void PingFunctor::operator()(BabelCoreClient & core, void *data)
{

}
