#ifndef OPUS_AUDIO_CODER_HH
#define OPUS_AUDIO_CODER_HH

#include <stdint.h>
#include <opus/opus.h>
#include "IAudioCoder.hh"

class OpusAudioCoder : public IAudioCoder
{
public:
  OpusAudioCoder(size_t samplingRate, size_t nbrChannels, size_t bitRate);
  ~OpusAudioCoder();

  uint32_t	decode(int16_t* audioRaw, const unsigned char* packetData);
  uint32_t	encode(const int16_t* audioRaw, unsigned char* packetData);
  void		setSamplingRate(size_t);
  void		setNbrChannels(size_t);
  void		setBitRate(size_t);
  size_t	getSamplingRate() const;
  size_t	getNbrChannels() const;
  size_t	getBitRate() const;


private:
  OpusEncoder*	m_encoder;
  OpusDecoder*	m_decoder;
  size_t	m_samplingRate;
  size_t	m_nbrChannels;
  size_t	m_bitRate;
};

#endif /* OPUS_AUDIO_CODER_HH */
