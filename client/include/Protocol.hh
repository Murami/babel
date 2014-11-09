#ifndef PROTOCOL_HH
#define PROTOCOL_HH

#include <stdint.h>

namespace NET
{

#define IP_SIZE		0x40
#define LOGIN_SIZE	0x80
#define MD5_PASS_SIZE	0x80
#define MSG_SIZE	0x400
#define RAW_SIZE	500//0x1000
#define JPEG_SIZE	0x40000

  enum Type
    {
      T_HEADER		= 0,
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
    Type		type;
    uint32_t		size;
  } __attribute__((packed));

  struct LoginInfo
  {
    char			user[LOGIN_SIZE];
    char			md5_pass[MD5_PASS_SIZE];
  } __attribute__((packed));

  struct UserInfo
  {
    char			user[LOGIN_SIZE];
    Status		status;
  } __attribute__((packed));

  struct CallInfo
  {
    char			user[LOGIN_SIZE];
    char			ip[IP_SIZE];
    uint32_t		port;
    Protocol		prot;
    DataType		type;
  } __attribute__((packed));

  struct MsgInfo
  {
    char			user[LOGIN_SIZE];
    char			msg[MSG_SIZE];
  } __attribute__((packed));

  struct Sample
  {
    uint32_t		size;
    char			rawData[RAW_SIZE];
  } __attribute__((packed));

  struct Img
  {
    uint32_t		size;
    char			img[JPEG_SIZE];
  } __attribute__((packed));

  struct SamplePacket
  {
    Header header;
    Sample sample;
  } __attribute__((packed));

}

#endif
