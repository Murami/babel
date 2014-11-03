#include "BoostAsyncService.hh"

BoostAsyncService::BoostAsyncService()
{
}

BoostAsyncService::~BoostAsyncService()
{
}

boost::asio::io_service&	BoostAsyncService::getIOService()
{
  return (m_io_service);
};

void				BoostAsyncService::run()
{
  m_io_service.run();
}
