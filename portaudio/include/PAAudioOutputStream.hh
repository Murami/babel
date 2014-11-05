#ifndef PAAUDIOOUTPUTSTREAM_HH
#define PAAUDIOOUTPUTSTREAM_HH

#include "APAAudioStream.hh"
#include "IAudioOutputStream.hh"

class IAudioDevice;
class IAudioOutputStreamListener;

class PAAudioOutputStream : public APAAudioStream, public IAudioOutputStream
{
public:
  PAAudioOutputStream();
  ~PAAudioOutputStream();

  void	setOutputStream(IAudioDevice* inputDevice);
  void	setListener(IAudioOutputStreamListener* listener);
  void	open();
};

#endif /* PAAUDIOOUTPUTSTREAM_HH */
