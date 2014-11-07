#ifndef IAUDIOINPUTSTREAMLISTENER_HH
#define IAUDIOINPUTSTREAMLISTENER_HH

#include "SampleFormat.hh"

class IAudioInputStreamListener
{
public:
  virtual ~IAudioInputStreamListener() {};

  virtual int	onStreamRequest(const void* input, unsigned long frame,
				unsigned int channels, SampleFormat sampleFormat) = 0;
};

#endif /* IAUDIOINPUTSTREAMLISTENER_HH */
