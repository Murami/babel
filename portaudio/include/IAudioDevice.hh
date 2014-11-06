#ifndef IAUDIODEVICE_HH
#define IAUDIODEVICE_HH

class IAudioDevice
{
public:
  virtual ~IAudioDevice() {}

  virtual const char*	getName() const = 0;
  virtual unsigned int	getMaxInputChannels() const = 0;
  virtual unsigned int	getMaxOutputChannels() const = 0;
  virtual double	getDefaultSampleRate() const = 0;
  virtual unsigned int	getIndex() const = 0;
};

#endif /* IAUDIODEVICE_HH */
