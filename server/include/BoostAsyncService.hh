#ifndef BOOSTASYNCSERVICE_HH
#define BOOSTASYNCSERVICE_HH

#include <boost/asio.hpp>
#include "IAsyncService.hh"

class BoostAsyncService : public IAsyncService
{
private:
  boost::asio::io_service	m_io_service;

public:
  BoostAsyncService();
  virtual ~BoostAsyncService();

  boost::asio::io_service&	getIOService();
  void				run();
};

#endif /* BOOSTASYNCSERVICE_HH */
