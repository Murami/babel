#include "PAAudioService.hh"
#include "PAAudioDevice.hh"

#include <cstdlib>
#include <portaudio.h>

#include <iostream>

PAAudioService*	PAAudioService::m_instance = NULL;

PAAudioService::PAAudioService()
{

}

PAAudioService::~PAAudioService()
{
  if (this->isInitialized())
    this->release();
}

PAAudioService*		PAAudioService::getInstance()
{
  if (m_instance == NULL)
    m_instance = new PAAudioService;
  return (m_instance);
}

void			PAAudioService::deleteInstance()
{
  if (m_instance != NULL)
    delete m_instance;
  m_instance = NULL;
}

void			PAAudioService::initialize()
{
  Pa_Initialize();
  m_initialized = true;
}

void			PAAudioService::release()
{
  Pa_Terminate();
  m_initialized = false;
}

unsigned int		PAAudioService::getDeviceCount() const
{
  return (Pa_GetDeviceCount());
}

bool			PAAudioService::isInitialized() const
{
  return (m_initialized);
}

IAudioDevice*		PAAudioService::getDefaultInputDevice() const
{
  return (getDevice(Pa_GetDefaultInputDevice()));
}

IAudioDevice*		PAAudioService::getDefaultOutputDevice() const
{
  return (getDevice(Pa_GetDefaultOutputDevice()));
}

IAudioDevice*		PAAudioService::getDevice(unsigned int index) const
{
  if (index >= getDeviceCount())
    return (NULL);
  return (new PAAudioDevice(index));
}

unsigned int		PAAudioService::getPaSampleFormat(SampleFormat sampleFormat) const
{
  return (1 << sampleFormat);
}
