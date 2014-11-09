#ifndef _BABEL_PROTOCOL_HH_
# define _BABEL_PROTOCOL_HH_

#ifdef WIN32
# define PACKED(__body__) __pragma(pack(push, 1)) struct __body__ __pragma(pack(pop))
#else
# define PACKED(__body__) struct __attribute__((packed)) __body__
#endif

# include <stdint.h>

# define PORT		1234
# define IP_SIZE       	0x40//64
# define LOGIN_SIZE	0x80//128
# define MD5_PASS_SIZE	0x80//128
# define MSG_SIZE	0x400//1024
# define RAW_SIZE	0x1000//4096
# define JPEG_SIZE	0x6000//262144

enum Type
  {
    HEADER = 0,
    LOGIN = 1,
    LOGOUT = 2,
    REGISTER = 3,
    USERINFO = 4,
    SENDMSG = 5,
    RECVMSG = 6,
    CALL = 7,
    HANGOUT = 8,
    OK_LOGIN = 9,
    KO_LOGIN = 10,
    OK_REGISTER = 11,
    KO_REGISTER = 12,
    OK_CALL = 13,
    KO_CALL = 14,
    OK_MSG = 15,
    KO_MSG = 16,
    SAMPLE = 17,
    IMG = 18,
    PING = 19,
    UNKNOWN
  };

enum Status{CONNECTED = 1, DISCONNECTED = 2};
enum Protocol {TCP = 1, UDP = 2};
enum DataType {AUDIO = 1, VIDEO = 2};

PACKED(Header
{
  Type		type;
  uint32_t	size;
};)

PACKED(LoginInfo
{
  char		user[LOGIN_SIZE];
  char		md5_pass[MD5_PASS_SIZE];
};)

PACKED(UserInfo
{
  char		user[LOGIN_SIZE];
  Status	status;
};)

PACKED(Call
{
  char		user[LOGIN_SIZE];
  char		ip[IP_SIZE];
  uint32_t	port;
  Protocol	prot;
  DataType	type;
};)

PACKED(Msg
{
  char		user[LOGIN_SIZE];
  char		msg[MSG_SIZE];
};)

PACKED(Sample
{
  uint32_t	size;
  char		rawData[RAW_SIZE];
};)

PACKED(Img
{
  uint32_t	size;
  char		img[JPEG_SIZE];
};)

#endif /* _BABEL_PROTOCOL_HH_ */
