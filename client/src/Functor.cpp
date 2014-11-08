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
  std::cout << "recv ok call" << std::endl;
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyCallError(true);
  core.getRecorder()->start();
  core.getPlayer()->start();
  core.getTimer().start();
}

void KoCallFunctor::operator()(BabelCoreClient & core, void *data)
{
  std::cout << "recv ko call" << std::endl;
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.notifyCallError(false);
  core.getTimer().stop();
  if (core.getPlayer->active())
    core.getPlayer()->stop();
  if (core.getPlayer->active())
    core.getRecorder()->stop();
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
  std::cout << "recv kologin" << std::endl;
  (void)data;
  core.setTypeNeeded(NET::T_HEADER);
  core.onPing();
}
