#ifndef _BABEL_PROTOCOL_HH_
# define _BABEL_PROTOCOL_HH_

# include <stdint.h>

# define PORT		1234
# define IP_SIZE       	0x40//64
# define LOGIN_SIZE	0x80//128
# define MD5_PASS_SIZE	0x80//128
# define MSG_SIZE	0x400//1024
# define RAW_SIZE	0x1000//4096
# define JPEG_SIZE	0x40000//262144

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
    PING = 19
  };

enum Status{CONNECTED = 1, DISCONNECTED = 2};
enum Protocol {TCP = 1, UDP = 2};
enum DataType {AUDIO = 1, VIDEO = 2};

struct		Header
{
  Type		type;
  uint32_t	size;
}__attribute__((packed));

struct		LoginInfo
{
  char		user[LOGIN_SIZE];
  char		md5_pass[MD5_PASS_SIZE];
}__attribute__((packed));

struct		UserInfo
{
  char		user[LOGIN_SIZE];
  Status	status;
}__attribute__((packed));

struct		Call
{
  char		user[LOGIN_SIZE];
  char		ip[IP_SIZE];
  size_t	port;
  Protocol	prot;
  DataType	type;
}__attribute__((packed));

struct		Msg
{
  char		user[LOGIN_SIZE];
  char		msg[MSG_SIZE];
}__attribute__((packed));

struct Sample
{
  size_t	size;
  char		rawData[RAW_SIZE];
}__attribute__((packed));

struct Img
{
  size_t	size;
  char		img[JPEG_SIZE];
}__attribute__((packed));

#endif /* _BABEL_PROTOCOL_HH_ */
