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

      // core.setUdpAddress("127.0.0.1");
      // core.setUdpPort(1235);

      // core.getRecorder()->start();
      // core.getPlayer()->start();
      // core.getTimer().start();
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
      if (core.getTimer().isActive() == false)
      	core.getTimer().start();
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
      if (core.getTimer().isActive() == true)
	core.getTimer().stop();
      if (core.getPlayer()->active() == true)
	core.getPlayer()->stop();
      if (core.getRecorder()->active() == true)
	core.getRecorder()->stop();
      core.disconnectAudio();
      std::cout << "\033[41mKO CALL\033[0m" << std::endl;
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

void SampleFunctor::operator()(BabelCoreClient & core, void *data)
{
}

void ImgFunctor::operator()(BabelCoreClient & core, void *data)
{

}

void PingFunctor::operator()(BabelCoreClient & core, void *data)
{
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.onPing();
}
