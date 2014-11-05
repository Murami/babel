#ifndef IAUDIOSTREAMLISTENER_HH
#define IAUDIOSTREAMLISTENER_HH

class IAudioStreamListener
{
public:
  virtual int	onStreamRequest(const void* input, void* output, unsigned long framesPerBuffer);
};

#endif /* IAUDIOSTREAMLISTENER_HH */
