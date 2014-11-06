#ifndef IAUDIOOUTPUTSTREAM_HH
#define IAUDIOOUTPUTSTREAM_HH

#include "APAAudioStream.hh"

class IAudioDevice;
class IAudioOutputStreamListener;

class IAudioOutputStream : public IAudioStream
{
public:
  virtual ~IAudioOutputStream() {};

  virtual void	setOutputDevice(IAudioDevice* inputDevice) = 0;
  virtual void	setListener(IAudioOutputStreamListener* listener) = 0;
};

#endif /* IAUDIOOUTPUTSTREAM_HH */
