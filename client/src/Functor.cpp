#include <iostream>
#include "Functor.hh"
#include "Protocol.hh"
#include "BabelCoreClient.hh"

void UserInfoFunctor::operator()(BabelCoreClient & core, void *data)
{
  std::cout << "recv userinfo" << std::endl;
  if (core.getTypeNeeded() == NET::T_HEADER)
    {
      std::cout << "test1" << std::endl;
      core.setTypeNeeded(NET::T_USERINFO);
    }
  else
    {
      std::cout << "test2" << std::endl;
      core.setTypeNeeded(NET::T_HEADER);
      NET::UserInfo *tmp = reinterpret_cast<NET::UserInfo*>(data);
      core.notifyUserInfo(*tmp);
    }
}

void RecvMsgFunctor::operator()(BabelCoreClient & core, void *data)
{
  std::cout << "recv msg" << std::endl;
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
  std::cout << "recv call" << std::endl;
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
  std::cout << "recv ok login" << std::endl;
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyLogin(true);
}

void KoLoginFunctor::operator()(BabelCoreClient & core, void *data)
{
  std::cout << "recv kologin" << std::endl;
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyLogin(false);
}

void OkRegisterFunctor::operator()(BabelCoreClient & core, void *data)
{
  std::cout << "recv ok register" << std::endl;
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyRegister(true);
}

void KoRegisterFunctor::operator()(BabelCoreClient & core, void *data)
{
  std::cout << "recv ko register" << std::endl;
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
    }
}

void OkMsgFunctor::operator()(BabelCoreClient & core, void *data)
{
  std::cout << "recv ok msg" << std::endl;
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyMsgError(true);
}

void KoMsgFunctor::operator()(BabelCoreClient & core, void *data)
{
  std::cout << "recv ko message" << std::endl;
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
  std::cout << "recv ping" << std::endl;
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.onPing();
}
