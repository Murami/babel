#ifndef PAAUDIOINPUTSTREAM_HH
#define PAAUDIOINPUTSTREAM_HH

#include "APAAudioStream.hh"
#include "IAudioInputStream.hh"

class PAAudioInputStream : public APAAudioStream, public IAudioInputStream
{
public:
  PAAudioInputStream();
  ~PAAudioInputStream();

  void	setInputStream(IAudioDevice* inputDevice);
  void	setListener(IAudioInputStreamListener* listener);
  void	open();
};

#endif /* PAAUDIOINPUTSTREAM_HH */
