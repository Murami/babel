#ifndef IAUDIOINPUTSTREAMLISTENER_HH
#define IAUDIOINPUTSTREAMLISTENER_HH

class IAudioInputStreamListener
{
public:
  virtual int	onStreamRequest(const void* input, unsigned long frame, unsigned int channels);
};

#endif /* IAUDIOINPUTSTREAMLISTENER_HH */
