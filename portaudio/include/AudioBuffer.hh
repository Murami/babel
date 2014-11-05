#ifndef AUDIOBUFFER_HH
#define AUDIOBUFFER_HH

class CircularBuffer;

class AudioBuffer
{
private:
  CircularBuffer*	m_buffer;
  unsigned int		m_channels;
  unsigned int		m_sampleRate;
  unsigned int		m_maxFrame;
  unsigned int		m_size;

public:
  AudioBuffer(unsigned int channels, unsigned int sampleRate, unsigned int frameCount);
  AudioBuffer(unsigned int channels, unsigned int sampleRate,
	      unsigned int second, unsigned int millisecond);
  ~AudioBuffer();

  unsigned int	channels() const;
  unsigned int	sampleRate() const;
  unsigned int	maxFrame() const;
  unsigned int	size() const;
  void*		data() const;
};

#endif /* AUDIOBUFFER_HH */
