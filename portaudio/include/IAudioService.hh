#ifndef IAUDIOSERVICE_HH
#define IAUDIOSERVICE_HH

class IAudioDevice;

class IAudioService
{
public:
  virtual ~IAudioService() {};

  virtual void			initialize() = 0;
  virtual void			release() = 0;
  virtual bool			isInitialized() const = 0;
  virtual unsigned int		getDeviceCount() const = 0;
  virtual IAudioDevice*		getDefaultInputDevice() const = 0;
  virtual IAudioDevice*		getDefaultOutputDevice() const = 0;
  virtual IAudioDevice*		getDevice(unsigned int index) const = 0;
};

#endif /* IAUDIOSERVICE_HH */
