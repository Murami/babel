#ifndef PAAUDIODEVICE_HH
#define PAAUDIODEVICE_HH

#include "IAudioDevice.hh"

class PAAudioDevice : public IAudioDevice
{
public:
  PAAudioDevice(unsigned int index);
  ~PAAudioDevice();

  const char*	getName() const;
  unsigned int	getMaxInputChannels() const;
  unsigned int	getMaxOutputChannels() const;
  double	getDefaultSampleRate() const;
  unsigned int	getIndex() const;
};

#endif /* PAAUDIODEVICE_HH */
