#ifndef IAUDIOINPUTSTREAM_HH
#define IAUDIOINPUTSTREAM_HH

#include "IAudioStream.hh"
#include "IAudioInputStream.hh"

class IAudioDevice;
class IAudioInputStreamListener;

class IAudioInputStream : public IAudioStream
{
public:
  virtual void	setInputStream(IAudioDevice* inputDevice);
  virtual void	setListener(IAudioInputStreamListener* listener);
};

#endif /* IAUDIOINPUTSTREAM_HH */
