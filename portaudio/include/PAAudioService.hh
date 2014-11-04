#ifndef PAAUDIOSERVICE_HH
#define PAAUDIOSERVICE_HH

#include "IAudioService.hh"

class PAAudioService : public IAudioService
{
private:
  bool				m_initialized;

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
  unsigned int			getDefaultInputDevice() const;
  unsigned int			getDefaultOutputDevice() const;
};

#endif /* PAAUDIOSERVICE_HH */
