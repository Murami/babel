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

enum Type
  {
    HEADER		= 0,
    LOGIN		= 1,
    LOGOUT		= 2,
    REGISTER		= 3,
    USERINFO		= 4,
    SENDMSG		= 5,
    RECVMSG		= 6,
    CALL		= 7,
    HANGOUT		= 8,
    OK_LOGIN		= 9,
    KO_LOGIN		= 10,
    OK_REGISTER		= 11,
    KO_REGISTER		= 12,
    OK_CALL		= 13,
    KO_CALL		= 14,
    SAMPLE		= 15,
    IMG			= 16,
    PING		= 17
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
  Type			type;
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
