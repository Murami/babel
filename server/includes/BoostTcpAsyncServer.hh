//
// BoostTcpAsyncServer.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 22:28:42 2014 anto
// Last update Tue Oct 21 22:32:56 2014 anto
//

#ifndef BOOSTTCPASYNCSERVER_HH
#define BOOSTTCPASYNCSERVER_HH

#include "TcpAsyncServer.hh"

class BoostTcpAsynServer : public TcpAsyncServer
{
private:
  boost::asio::io_service	m_io_service;

public:
  boost::asio::io_service	getIOService();
  void				run();
};

#endif /* BOOSTTCPASYNCSERVER_HH */
