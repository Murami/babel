#include "PAAudioDevice.hh"

#include <portaudio.h>

PAAudioDevice::PAAudioDevice(unsigned int index) :
  m_index(index)
{
}

PAAudioDevice::~PAAudioDevice()
{
}

const char*	PAAudioDevice::getName() const
{
  return (Pa_GetDeviceInfo(m_index)->name);
}

unsigned int	PAAudioDevice::getMaxInputChannels() const
{
  return (Pa_GetDeviceInfo(m_index)->maxInputChannels);
}

unsigned int	PAAudioDevice::getMaxOutputChannels() const
{
  return (Pa_GetDeviceInfo(m_index)->maxOutputChannels);
}

double		PAAudioDevice::getDefaultSampleRate() const
{
  return (Pa_GetDeviceInfo(m_index)->defaultSampleRate);
}

unsigned int	PAAudioDevice::getIndex() const
{
  return (m_index);
}
