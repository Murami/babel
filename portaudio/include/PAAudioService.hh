#ifndef PAAUDIOSERVICE_HH
#define PAAUDIOSERVICE_HH

#include "IAudioService.hh"

class AudioDevice;

class PAAudioService : public IAudioService
{
private:
  bool				m_initialized;
  static PAAudioService*	m_instance;

private:
  PAAudioService();
  ~PAAudioService();

public:
  static PAAudioService*	getInstance();
  static void			deleteInstance();

  void				initialize();
  void				release();
  bool				isInitialized() const;
  unsigned int			getDeviceCount() const;
  IAudioDevice*			getDefaultInputDevice() const;
  IAudioDevice*			getDefaultOutputDevice() const;
  IAudioDevice*			getDevice(unsigned int index) const;
};

#endif /* PAAUDIOSERVICE_HH */
