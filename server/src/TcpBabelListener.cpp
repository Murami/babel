#include "TcpBabelListener.hh"

TcpBabelListener()
{

}

~TcpBabelListener()
{

}

void	onAccept(TcpAsyncServer& server, TcpAsyncClient* client)
{

}

void	onRead(TcpAsyncClient* client)
{

}

void	onTimeout(TcpAsyncServer* server)
{

}

void	onCall(TcpAsyncClient& client, LoginInfo& loginInfo)
{

}

void	onLogin(TcpAsyncClient& client, UserInfos& userInfo)
{

}

void	onLogout(TcpAsyncClient& client)
{

}

void	onRegister(TcpAsyncClient& client, UserInfo& userInfo)
{

}

void	onSendmsg(TcpAsyncClient& client, MsgInfo& msgInfos)
{

}
