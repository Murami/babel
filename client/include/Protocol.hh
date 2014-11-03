#ifndef PROTOCOL_HH
#define PROTOCOL_HH

namespace NET
{

#define IP_SIZE		0x40
#define LOGIN_SIZE	0x80
#define MD5_PASS_SIZE	0x80
#define MSG_SIZE	0x400
#define RAW_SIZE	0x1000
#define JPEG_SIZE	0x40000

enum HeaderType
  {
    T_LOGIN		= 1,
    T_LOGOUT		= 2,
    T_REGISTER		= 3,
    T_USERINFO		= 4,
    T_SENDMSG		= 5,
    T_RECVMSG		= 6,
    T_CALL		= 7,
    T_HANGOUT		= 8,
    T_OK_LOGIN		= 9,
    T_KO_LOGIN		= 10,
    T_OK_REGISTER	= 11,
    T_KO_REGISTER	= 12,
    T_OK_CALL		= 13,
    T_KO_CALL		= 14,
    T_OK_MSG		= 15,
    T_KO_MSG		= 16,
    T_SAMPLE		= 17,
    T_IMG		= 18,
    T_PING		= 19
  };

enum StructType
  {
    S_HEADER		= 1,
    S_LOGIN		= 2,
    S_USER		= 3,
    S_CALL		= 4,
    S_MSG		= 5
  };

enum Status
  {
    CONNECTED		= 1,
    DISCONNECTED	= 2
  };

enum Protocol
  {
    TCP			= 1,
    UDP			= 2
  };

enum DataType
  {
    AUDIO		= 1,
    VIDEO		= 2
  };

struct Header
{
  HeaderType			type;
  size_t		size;
};

struct LoginInfo
{
  char			user[LOGIN_SIZE];
  char			md5_pass[MD5_PASS_SIZE];
};

struct UserInfo
{
  char			user[LOGIN_SIZE];
  Status		status;
};

struct CallInfo
{
  char			user[LOGIN_SIZE];
  char			ip[IP_SIZE];
  size_t		port;
  Protocol		prot;
  DataType		type;
};

struct MsgInfo
{
  char			user[LOGIN_SIZE];
  char			msg[MSG_SIZE];
};

struct Sample
{
  size_t		size;
  char			rawData[RAW_SIZE];
};

struct Img
{
  size_t		size;
  char			img[JPEG_SIZE];
};

}

#endif
