#ifndef IAUDIOCODER_HH
#define IAUDIOCODER_HH

#include <cstdlib>
#include <stdint.h>

class AudioBuffer;

class IAudioCoder
{
public:
  virtual uint32_t	decode(int16_t* audioRaw, const unsigned char* packetData) = 0;
  virtual uint32_t	encode(const int16_t* audioRaw, unsigned char* packetData) = 0;
  virtual void		setSamplingRate(size_t) = 0;
  virtual void		setNbrChannels(size_t) = 0;
  virtual void		setBitRate(size_t) = 0;
  virtual size_t	getSamplingRate() const = 0;
  virtual size_t	getNbrChannels() const = 0;
  virtual size_t	getBitRate() const = 0;
};

#endif /* IAUDIOCODER_HH */
