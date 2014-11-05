#ifndef IAUDIOOUTPUTSTREAM_HH
#define IAUDIOOUTPUTSTREAM_HH

#include "APAAudioStream.hh"

class IAudioOutputStream : public IAudioStream
{
public:
  virtual void	setOutputStream(IAudioDevice* inputDevice);
  virtual void	setListener(IAudioInputStreamListener* listener);
};

#endif /* IAUDIOOUTPUTSTREAM_HH */
