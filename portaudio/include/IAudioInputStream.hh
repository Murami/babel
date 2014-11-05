#ifndef IAUDIOINPUTSTREAM_HH
#define IAUDIOINPUTSTREAM_HH

#include "IAudioStream.hh"
#include "IAudioInputStream.hh"

class IAudioDevice;
class IAudioInputStreamListener;

class IAudioInputStream : public IAudioStream
{
public:
  virtual ~IAudioInputStream() {};

  virtual	void	setInputDevice(IAudioDevice* inputDevice) = 0;
  virtual	void	setListener(IAudioInputStreamListener* listener) = 0;
};

#endif /* IAUDIOINPUTSTREAM_HH */
