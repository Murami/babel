#include "AudioBuffer.hh"

AudioBuffer::AudioBuffer(unsigned int channels, unsigned int sampleRate, unsigned int frameCount)
{
  AudioBuffer	buffer;

  m_channels = channels;
  m_sampleRate = sampleRate;
  m_maxFrame = frameCount;
  m_size = frameCount * channels * sizeof(uint16_t);
  m_data = new CircularBuffer(m_size);
}

AudioBuffer::AudioBuffer(unsigned int channels, unsigned int sampleRate,
			 unsigned int second, unsigned int millisecond)
{
  m_channels = channels;
  m_sampleRate = sampleRate;
  m_maxFrame = (sampleRate * millisecond) / 1000 + sampleRate * second;
  m_size = buffer.maxFrame * channels * sizeof(uint16_t);
  m_data = new CircularBuffer(m_size);
}

~AudioBuffer::AudioBuffer()
{
  delete[] m_data;
}

unsigned int	AudioBuffer::channels() const
{
  return (m_channels);
}

unsigned int	AudioBuffer::sampleRate() const
{
  return (m_sampleRate);
}

unsigned int	AudioBuffer::maxFrame() const
{
  return (m_maxFrame);
}

unsigned int	AudioBuffer::size() const
{
  return (m_size);
}

void*		AudioBuffer::data() const
{
  return (m_buffer);
}
