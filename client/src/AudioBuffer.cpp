#include "AudioBuffer.hh"
#include "CircularBuffer.hh"

#include <cstdlib>
#include <iostream>

AudioBuffer::AudioBuffer(unsigned int channels,
			 unsigned int sampleRate,
			 unsigned int frameCount,
			 SampleFormat sampleFormat) :
  m_channels(channels),
  m_sampleRate(sampleRate),
  m_maxFrame(frameCount),
  m_sampleFormat(sampleFormat)
{
  size_t	size = frameCount * channels * g_sampleFormatSizes[sampleFormat];

  m_buffer = new char[size];
}

AudioBuffer::AudioBuffer(unsigned int channels,
			 unsigned int sampleRate,
			 unsigned int second,
			 unsigned int millisecond,
			 SampleFormat sampleFormat) :
  m_channels(channels),
  m_sampleRate(sampleRate),
  m_sampleFormat(sampleFormat)
{
  size_t	size;

  m_maxFrame = (sampleRate * millisecond) / 1000 + sampleRate * second;
  size = m_maxFrame * channels * g_sampleFormatSizes[sampleFormat];
  m_buffer = new char[size];
}

AudioBuffer::~AudioBuffer()
{
  delete[]	m_buffer;
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

SampleFormat	AudioBuffer::sampleFormat() const
{
  return (m_sampleFormat);
}


void*		AudioBuffer::data() const
{
  return (m_buffer);
}
