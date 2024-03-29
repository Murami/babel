#include <iostream>
#include "Functor.hh"
#include "Protocol.hh"
#include "BabelCoreClient.hh"

void UserInfoFunctor::operator()(BabelCoreClient & core, void *data)
{
  if (core.getTypeNeeded() == NET::T_HEADER)
    {
      core.setTypeNeeded(NET::T_USERINFO);
    }
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
      core.setUdpAddress(tmp->ip);
      core.setUdpPort(tmp->port);
    }
}

void OkLoginFunctor::operator()(BabelCoreClient & core, void *data)
{
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyLogin(true);
}

void KoLoginFunctor::operator()(BabelCoreClient & core, void *data)
{
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyLogin(false);
}

void OkRegisterFunctor::operator()(BabelCoreClient & core, void *data)
{
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyRegister(true);
}

void KoRegisterFunctor::operator()(BabelCoreClient & core, void *data)
{
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyRegister(false);
}

void OkCallFunctor::operator()(BabelCoreClient & core, void *data)
{
  if (core.getTypeNeeded() == NET::T_HEADER)
    core.setTypeNeeded(NET::T_OK_CALL);
  else
    {
      NET::UserInfo *tmp = reinterpret_cast<NET::UserInfo*>(data);
      core.setTypeNeeded(NET::T_USERINFO);
      core.notifyCallError(true, *tmp);

      core.connectAudio();

      if (core.getRecorder()->active() == false)
      	core.getRecorder()->start();
      if (core.getPlayer()->active() == false)
      	core.getPlayer()->start();
    }
}

void KoCallFunctor::operator()(BabelCoreClient & core, void *data)
{
  if (core.getTypeNeeded() == NET::T_HEADER)
    core.setTypeNeeded(NET::T_KO_CALL);
  else
    {
      core.setTypeNeeded(NET::T_USERINFO);
      NET::UserInfo *tmp = reinterpret_cast<NET::UserInfo*>(data);
      core.notifyCallError(false, *tmp);
      if (core.getPlayer()->active() == true)
	core.getPlayer()->stop();
      if (core.getRecorder()->active() == true)
	core.getRecorder()->stop();
      core.disconnectAudio();
      core.notifyKoCall();
    }
}

void OkMsgFunctor::operator()(BabelCoreClient & core, void *data)
{
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyMsgError(true);
}

void KoMsgFunctor::operator()(BabelCoreClient & core, void *data)
{
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyMsgError(false);
}

void SampleFunctor::operator()(BabelCoreClient &, void *)
{
}

void ImgFunctor::operator()(BabelCoreClient &, void *)
{

}

void PingFunctor::operator()(BabelCoreClient & core, void *data)
{
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.onPing();
}
