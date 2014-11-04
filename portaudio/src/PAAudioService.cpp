#include "PAAudioService.hh"

#include <cstdlib>
#include <portaudio.h>

PAAudioService::PAAudioService()
{

}

PAAudioService::~PAAudioService()
{
  if (this->isInitialized())
    this->release();
}

void		PAAudioService::initialize()
{
  Pa_Initialize();
  m_initialized = true;
}

void		PAAudioService::release()
{
  Pa_Terminate();
  m_initialized = false;
}

unsigned int	PAAudioService::getDeviceCount() const
{
  return (Pa_GetDeviceCount());
}

bool		PAAudioService::isInitialized() const
{
  return (m_initialized);
}

unsigned int	PAAudioService::getDefaultInputDevice() const
{
  return (Pa_GetDefaultInputDevice());
}

unsigned int	PAAudioService::getDefaultOutputDevice() const
{
  return (Pa_GetDefaultOutputDevice());
}
