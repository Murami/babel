#ifndef IAUDIOOUTPUTSTREAMLISTENER_HH
#define IAUDIOOUTPUTSTREAMLISTENER_HH

#include "SampleFormat.hh"

class IAudioOutputStreamListener
{
public:
  virtual ~IAudioOutputStreamListener() {};
  virtual int	onStreamRequest(void* output, unsigned long frame,
				unsigned int channels, SampleFormat sampleFrormat) = 0;
};

#endif /* IAUDIOOUTPUTSTREAMLISTENER_HH */
