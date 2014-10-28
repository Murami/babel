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
  ~BoostAsyncService();

  void	getIOService();
  void	run();
};

#endif /* BOOSTASYNCSERVICE_HH */
