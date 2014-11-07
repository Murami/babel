#ifndef AUDIOBUFFER_HH
#define AUDIOBUFFER_HH

#include "SampleFormat.hh"

// class CircularBuffer;
class BasicBuffer;

class AudioBuffer
{
private:
  char*			m_buffer;
  unsigned int		m_channels;
  unsigned int		m_sampleRate;
  unsigned int		m_maxFrame;
  SampleFormat		m_sampleFormat;

public:
  AudioBuffer(unsigned int channels, unsigned int sampleRate,
	      unsigned int frameCount, SampleFormat sampleFormat);
  AudioBuffer(unsigned int channels, unsigned int sampleRate,
	      unsigned int second, unsigned int millisecond,
	      SampleFormat sampleFormat);
  ~AudioBuffer();

  unsigned int	channels() const;
  unsigned int	sampleRate() const;
  unsigned int	maxFrame() const;
  SampleFormat	sampleFormat() const;

  void*		data() const;
};

#endif /* AUDIOBUFFER_HH */
